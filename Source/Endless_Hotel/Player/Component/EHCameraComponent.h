// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Component/EHComponent.h"
#include "EHCameraComponent.generated.h"

UCLASS()
class ENDLESS_HOTEL_API UEHCameraComponent : public UEHComponent
{
	GENERATED_BODY()
	
#pragma region Base

public:
	UEHCameraComponent(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Post Processing

protected:
	UPROPERTY()
	TObjectPtr<APostProcessVolume> PostProcessVolume;

#pragma endregion

#pragma region Eye Effect

public:
	void StartEyeEffect(bool bIsOpen);

protected:
	void SettingEyeEffect();

	UFUNCTION()
	void ApplyEyeEffect(float Value);

	UFUNCTION()
	void EndEyeEffect();

protected:
	UPROPERTY()
	TObjectPtr<class UTimelineComponent> Timeline_EyeEffect;

	UPROPERTY(EditAnywhere, Category = "EyeEffect")
	TSubclassOf<class UUI_Base> UI_Blur;

	UPROPERTY(EditAnywhere, Category = "EyeEffect")
	TObjectPtr<UCurveFloat> Curve_EyeOpen;

	UPROPERTY(EditAnywhere, Category = "EyeEffect")
	TObjectPtr<UCurveFloat> Curve_EyeClose;

	UPROPERTY(EditAnywhere, Category = "EyeEffect")
	TObjectPtr<UMaterial> Mat_EyeEffect;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynMat_EyeEffect;

#pragma endregion

};