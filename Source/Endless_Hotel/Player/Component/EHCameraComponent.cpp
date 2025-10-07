// Copyright by 2025-2 WAP Game 2 team

#include "Player/Component/EHCameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TimelineComponent.h"

#pragma region Base

UEHCameraComponent::UEHCameraComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;

	Timeline_EyeEffect = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_EyeEffect"));
}

void UEHCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	SettingEyeEffect();
	StartEyeEffect();
}

#pragma endregion

#pragma region Eye Effect

void UEHCameraComponent::SettingEyeEffect()
{
	FOnTimelineFloat UpdateFunc;
	UpdateFunc.BindUFunction(this, FName("EyeEffect"));
	Timeline_EyeEffect->AddInterpFloat(Curve_EyeEffect, UpdateFunc);

	FOnTimelineEvent FinishFunc;
	FinishFunc.BindUFunction(this, FName("EndEyeEffect"));
	Timeline_EyeEffect->SetTimelineFinishedFunc(FinishFunc);
}

void UEHCameraComponent::StartEyeEffect()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APostProcessVolume::StaticClass(), FoundActors);
	PostProcessVolume = Cast<APostProcessVolume>(FoundActors[0]);

	DynMat_EyeEffect = UMaterialInstanceDynamic::Create(Mat_EyeEffect, this);

	PostProcessVolume->bUnbound = true;
	PostProcessVolume->Settings.WeightedBlendables.Array.Empty();
	PostProcessVolume->Settings.WeightedBlendables.Array.Add(FWeightedBlendable(1, DynMat_EyeEffect));

	Timeline_EyeEffect->PlayFromStart();
}

void UEHCameraComponent::EyeEffect(float Value)
{
	DynMat_EyeEffect->SetScalarParameterValue(FName("EyeOpen"), Value);
}

void UEHCameraComponent::EndEyeEffect()
{
	PostProcessVolume->Settings.WeightedBlendables.Array.Empty();
}

#pragma endregion