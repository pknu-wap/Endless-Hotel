// Copyright by 2025-2 WAP Game 2 team

#include "Player/Component/EHCameraComponent.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/HUD/InGame/UI_HUD_InGame.h"
#include "Sound/SoundController.h"
#include "Actor/Elevator/Elevator.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "Type/Level/Type_Level.h"
#include <EngineUtils.h>
#include <Engine/PostProcessVolume.h>

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

	for (TActorIterator<APostProcessVolume> It(GetWorld()); It; ++It)
	{
		if (It->ActorHasTag(TEXT("Eye")))
		{
			PostProcessVolume = *It;
		}
	}
}

#pragma endregion

#pragma region Eye Effect

void UEHCameraComponent::SettingEyeEffect()
{
	DynMat_EyeEffect = UMaterialInstanceDynamic::Create(Mat_EyeEffect, this);

	PostProcessVolume->Settings.WeightedBlendables.Array.Empty();
	PostProcessVolume->Settings.WeightedBlendables.Array.Add(FWeightedBlendable(1, DynMat_EyeEffect));

	FOnTimelineFloat Update_Open;
	Update_Open.BindUFunction(this, FName("ApplyEyeEffect"));
	TL_EyeEffect.AddInterpFloat(Curve_EyeOpen.Get(), Update_Open);
}

void UEHCameraComponent::StartEyeEffect(bool bIsOpen)
{
	UUI_Controller* UICon = GetWorld()->GetGameInstance()->GetSubsystem<UUI_Controller>();
	UUI_HUD_InGame* UI_InGame = Cast<UUI_HUD_InGame>(UICon->GetCurrentBaseWidget());

	USoundController* SoundCon = GetWorld()->GetGameInstance()->GetSubsystem<USoundController>();
	SoundCon->FadeSFXSound(bIsOpen);

	constexpr float RemoveDuration = 5.f;

	if (bIsOpen)
	{
		UI_InGame->EyeEffectBlur(true);
		TL_EyeEffect.PlayFromStart();
	}
	else
	{
		UI_InGame->EyeEffectBlur(false);
		TL_EyeEffect.ReverseFromEnd();
	}

	GetWorld()->GetTimerManager().SetTimer(RemoveHandle, this, &ThisClass::EndEyeEffect, RemoveDuration, false);
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
	}
}

#pragma endregion