// Copyright by 2025-2 WAP Game 2 team

#include "Player/Component/EHCameraComponent.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/HUD/InGame/UI_HUD_InGame.h"
#include "Sound/SoundController.h"
#include "Actor/Elevator/Elevator.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "Type/Level/Type_Level.h"

#pragma region Base

UEHCameraComponent::UEHCameraComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEHCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	AElevator::ElevatorDelegate.AddDynamic(this, &ThisClass::StartEyeEffect);
	UEHGameInstance::OnLevelShown.AddDynamic(this, &ThisClass::LevelShownCompleted);

	FindPPV();
	SettingEyeEffect();
}

void UEHCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TL_EyeEffect.TickTimeline(DeltaTime);
}

#pragma endregion

#pragma region Post Processing

void UEHCameraComponent::FindPPV()
{
	PostProcessVolume = nullptr;

	for (auto* PPV : GetWorld()->PostProcessVolumes)
	{
		auto Props = PPV->GetProperties();
		if (Props.bIsUnbound)
		{
			PostProcessVolume = Cast<APostProcessVolume>(PPV);
			break;
		}
	}
}

#pragma endregion

#pragma region Eye Effect

void UEHCameraComponent::StartEyeEffect(bool bIsOpen)
{
	UUI_Controller* UICon = GetWorld()->GetGameInstance()->GetSubsystem<UUI_Controller>();
	UUI_HUD_InGame* UI_InGame = Cast<UUI_HUD_InGame>(UICon->GetCurrentBaseWidget());

	USoundController* SoundCon = GetWorld()->GetGameInstance()->GetSubsystem<USoundController>();
	SoundCon->FadeSFXSound(bIsOpen);

	EndEyeEffect();

	float RemoveDuration = 0.f;

	if (bIsOpen)
	{
		UI_InGame->EyeEffectBlur(true);
		TL_EyeEffect.PlayFromStart();
		RemoveDuration = 5.f;
	}
	else
	{
		UI_InGame->EyeEffectBlur(false);
		TL_EyeEffect.ReverseFromEnd();
		RemoveDuration = 5.f;
	}

	GetWorld()->GetTimerManager().SetTimer(RemoveHandle, this, &ThisClass::EndEyeEffect, RemoveDuration, false);
}

void UEHCameraComponent::SettingEyeEffect()
{
	DynMat_EyeEffect = UMaterialInstanceDynamic::Create(Mat_EyeEffect, this);

	PostProcessVolume->Settings.WeightedBlendables.Array.Empty();
	PostProcessVolume->Settings.WeightedBlendables.Array.Add(FWeightedBlendable(1, DynMat_EyeEffect));

	FOnTimelineFloat Update_Open;
	Update_Open.BindUFunction(this, FName("ApplyEyeEffect"));

	TL_EyeEffect.AddInterpFloat(Curve_EyeOpen, Update_Open);
	TL_EyeEffect.SetTimelineLength(20.f);
	TL_EyeEffect.SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);
	TL_EyeEffect.SetLooping(false);
}

void UEHCameraComponent::ApplyEyeEffect(float Value)
{
	DynMat_EyeEffect->SetScalarParameterValue(FName("EyeEffect"), Value);
}

void UEHCameraComponent::EndEyeEffect()
{
	TL_EyeEffect.Stop();
}

#pragma endregion

#pragma region Loading

void UEHCameraComponent::LevelShownCompleted()
{
	switch (UEHGameInstance::CurrentLevelType)
	{
	case ELevelType::Hotel:
		StartEyeEffect(true);
		break;

	case ELevelType::MainMenu:
		EndEyeEffect();
		GetWorld()->GetTimerManager().ClearTimer(RemoveHandle);
		break;
	}
}

#pragma endregion