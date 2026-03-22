// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Component/EHComponent.h"
#include <CoreMinimal.h>
#include <Components/TimelineComponent.h>
#include <EHCameraComponent.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UEHCameraComponent : public UEHComponent
{
	GENERATED_BODY()
	
#pragma region Base

public:
	UEHCameraComponent(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma endregion

#pragma region Post Processing

protected:
	void FindPPV();

protected:
	UPROPERTY()
	TWeakObjectPtr<APostProcessVolume> PostProcessVolume;

#pragma endregion

#pragma region Eye Effect

public:
	UFUNCTION()
	void StartEyeEffect(bool bIsOpen);

protected:
	void SettingEyeEffect();

	UFUNCTION()
	void ApplyEyeEffect(float Value);

	UFUNCTION()
	void EndEyeEffect();

protected:
	FTimeline TL_EyeEffect;

	UPROPERTY(EditAnywhere, Category = "EyeEffect")
	TObjectPtr<UCurveFloat> Curve_EyeOpen;

	UPROPERTY(EditAnywhere, Category = "EyeEffect")
	TObjectPtr<UMaterial> Mat_EyeEffect;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynMat_EyeEffect;

	FTimerHandle RemoveHandle;

#pragma endregion

#pragma region Loading

protected:
	UFUNCTION()
	void LevelShownCompleted();

#pragma endregion

};