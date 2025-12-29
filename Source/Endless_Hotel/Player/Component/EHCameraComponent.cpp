// Copyright by 2025-2 WAP Game 2 team

#include "Player/Component/EHCameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TimelineComponent.h"

#pragma region Base

UEHCameraComponent::UEHCameraComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Timeline_EyeEffect = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_EyeEffect"));
}

void UEHCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	SettingEyeEffect();
}

#pragma endregion

#pragma region Eye Effect

void UEHCameraComponent::StartEyeEffect(bool bIsOpen)
{
	if (bIsOpen)
	{
		Timeline_EyeEffect->SetFloatCurve(Curve_EyeOpen, FName("Eye"));
	}
	else
	{
		Timeline_EyeEffect->SetFloatCurve(Curve_EyeClose, FName("Eye"));
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APostProcessVolume::StaticClass(), FoundActors);
	PostProcessVolume = Cast<APostProcessVolume>(FoundActors[0]);

	DynMat_EyeEffect = UMaterialInstanceDynamic::Create(Mat_EyeEffect, this);

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