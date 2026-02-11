// Copyright by 2025-2 WAP Game 2 team

#include "Player/Component/EHCameraComponent.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/HUD/InGame/UI_HUD_InGame.h"
#include "Sound/SoundController.h"
#include "Actor/Elevator/Elevator.h"
#include "Anomaly/Base/Anomaly_Base.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "Type/Level/Type_Level.h"
#include <Kismet/GameplayStatics.h>
#include <Components/TimelineComponent.h>

#pragma region Base

UEHCameraComponent::UEHCameraComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Timeline_EyeEffect = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_EyeEffect"));

	AElevator::ElevatorDelegate.Clear();
	AElevator::ElevatorDelegate.AddDynamic(this, &ThisClass::StartEyeEffect);

	UEHGameInstance::OnLevelLoaded.Clear();
	UEHGameInstance::OnLevelLoaded.AddDynamic(this, &ThisClass::LevelLoadCompleted);
}

void UEHCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	SettingEyeEffect();
}

#pragma endregion

#pragma region Post Processing

void UEHCameraComponent::FindPPV()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APostProcessVolume::StaticClass(), OUT FoundActors);
	PostProcessVolume = Cast<APostProcessVolume>(FoundActors[0]);

	DynMat_EyeEffect = UMaterialInstanceDynamic::Create(Mat_EyeEffect, this);
}

#pragma endregion

#pragma region Eye Effect

void UEHCameraComponent::StartEyeEffect(bool bIsOpen)
{
	UUI_Controller* UICon = GetWorld()->GetGameInstance()->GetSubsystem<UUI_Controller>();
	UUI_HUD_InGame* UI_InGame = Cast<UUI_HUD_InGame>(UICon->GetCurrentBaseWidget());

	USoundController* SoundCon = GetWorld()->GetGameInstance()->GetSubsystem<USoundController>();
	SoundCon->FadeSFXSound(bIsOpen);

	if (bIsOpen)
	{
		UI_InGame->EyeEffectBlur(true);
		Timeline_EyeEffect->SetFloatCurve(Curve_EyeOpen, FName("Eye"));
	}
	else
	{
		UI_InGame->EyeEffectBlur(false);
		Timeline_EyeEffect->SetFloatCurve(Curve_EyeClose, FName("Eye"));
	}

	PostProcessVolume->bUnbound = true;
	PostProcessVolume->Settings.WeightedBlendables.Array.Empty();
	PostProcessVolume->Settings.WeightedBlendables.Array.Add(FWeightedBlendable(1, DynMat_EyeEffect));

	Timeline_EyeEffect->PlayFromStart();
}

void UEHCameraComponent::SettingEyeEffect()
{
	FOnTimelineFloat Update_Open;
	Update_Open.BindUFunction(this, FName("ApplyEyeEffect"));
	Timeline_EyeEffect->AddInterpFloat(Curve_EyeOpen, Update_Open, FName("Eye"), FName("Eye"));

	FOnTimelineEvent FinishFunc;
	FinishFunc.BindUFunction(this, FName("EndEyeEffect"));
	Timeline_EyeEffect->SetTimelineFinishedFunc(FinishFunc);
}

void UEHCameraComponent::ApplyEyeEffect(float Value)
{
	DynMat_EyeEffect->SetScalarParameterValue(FName("EyeEffect"), Value);
}

void UEHCameraComponent::EndEyeEffect()
{
	PostProcessVolume->Settings.WeightedBlendables.Array.Empty();
}

#pragma endregion

#pragma region Loading

void UEHCameraComponent::LevelLoadCompleted()
{
	switch (UEHGameInstance::CurrentLevelType)
	{
	case ELevelType::Hotel:
		FindPPV();
		StartEyeEffect(true);
		break;
	}
}

#pragma endregion