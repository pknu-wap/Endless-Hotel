// Copyright by 2025-2 WAP Game 2 team

#include "Player/Component/EHCameraComponent.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/HUD/InGame/UI_HUD_InGame.h"
#include "Sound/SoundController.h"
#include "Actor/Elevator/Elevator.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "Type/Level/Type_Level.h"
#include <Components/TimelineComponent.h>

#pragma region Base

UEHCameraComponent::UEHCameraComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Timeline_EyeEffect = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_EyeEffect"));
}

void UEHCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	AElevator::ElevatorDelegate.AddDynamic(this, &ThisClass::StartEyeEffect);
	UEHGameInstance::OnLevelShown.AddDynamic(this, &ThisClass::LevelShownCompleted);

	FindPPV();
	SettingEyeEffect();
}

#pragma endregion

#pragma region Post Processing

void UEHCameraComponent::FindPPV()
{
	if (PostProcessVolume.IsValid())
	{
		return;
	}

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

	PostProcessVolume->bUnbound = true;
	PostProcessVolume->Settings.WeightedBlendables.Array.Add(FWeightedBlendable(1, DynMat_EyeEffect));

	if (bIsOpen)
	{
		UI_InGame->EyeEffectBlur(true);
		Timeline_EyeEffect->SetNewTime(0.f);
		Timeline_EyeEffect->Play();
		FTimerHandle RemoveHandle;
		GetWorld()->GetTimerManager().SetTimer(RemoveHandle, this, &ThisClass::EndEyeEffect, 5, false);
	}
	else
	{
		UI_InGame->EyeEffectBlur(false);
		Timeline_EyeEffect->SetNewTime(9.f);
		Timeline_EyeEffect->Play();
	}
}

void UEHCameraComponent::SettingEyeEffect()
{
	DynMat_EyeEffect = UMaterialInstanceDynamic::Create(Mat_EyeEffect, this);

	FOnTimelineFloat Update_Open;
	Update_Open.BindUFunction(this, FName("ApplyEyeEffect"));
	Timeline_EyeEffect->AddInterpFloat(Curve_EyeOpen, Update_Open, FName("EyeTrack"));
}

void UEHCameraComponent::ApplyEyeEffect(float Value)
{
	DynMat_EyeEffect->SetScalarParameterValue(FName("EyeEffect"), Value);
}

void UEHCameraComponent::EndEyeEffect()
{
	Timeline_EyeEffect->Stop();
	PostProcessVolume->Settings.WeightedBlendables.Array.Empty();
}

#pragma endregion

#pragma region Loading

void UEHCameraComponent::LevelShownCompleted()
{
	switch (UEHGameInstance::CurrentLevelType)
	{
	case ELevelType::Hotel:
		EndEyeEffect();
		StartEyeEffect(true);
		break;
	}
}

#pragma endregion