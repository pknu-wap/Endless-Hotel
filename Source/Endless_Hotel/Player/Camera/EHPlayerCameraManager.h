// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Type/Level/Type_Level.h"
#include "Type/Camera/Type_Camera.h"
#include <CoreMinimal.h>
#include <Camera/PlayerCameraManager.h>
#include <EHPlayerCameraManager.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AEHPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AEHPlayerCameraManager(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Data Layer

private:
	UFUNCTION()
	void OnChangedDataLayer(const EMapDataLayer& DataLayer);

private:
	bool bIsFirstHotel = true;

#pragma endregion

#pragma region Post Processing

private:
	void FindPPV();

private:
	UPROPERTY()
	TWeakObjectPtr<APostProcessVolume> PPV_EyeEffect;

	UPROPERTY()
	TWeakObjectPtr<UMaterialInstanceDynamic> DM_EyeEffect;

#pragma endregion

#pragma region Eye

public:
	void StartEyeEffect(bool bIsOpen);
	void LoadingEyeEffect();

private:
	void SetEyeEffect();

	UFUNCTION()
	void OnValueChangedEyeEffect(float Value);

protected:
	UPROPERTY(EditAnywhere, Category = "EyeEffect")
	TObjectPtr<UMaterial> M_EyeEffect;

	UPROPERTY(EditAnywhere, Category = "EyeEffect")
	TObjectPtr<UCurveFloat> CV_EyeOpen;

	UPROPERTY(EditAnywhere, Category = "EyeEffect")
	TObjectPtr<UCurveFloat> CV_Loading;

private:
	FTimerHandle WaitHandle;

	UPROPERTY()
	TObjectPtr<class UTimelineComponent> TimeLine_Eye;

	UPROPERTY()
	TObjectPtr<class UTimelineComponent> TimeLine_Loading;

#pragma endregion

#pragma region Possess

public:
	void PossessCamera(const ECameraType& CameraType, const float& BlendTime = 0.f);
	void PossessCamera(AActor* CameraOwner, const float& BlendTime = 0.f);
	void PossessCameraToPlayer(const float& BlendTime = 0.f);

#pragma endregion

#pragma region Camera

public:
	void RegisterCamera(const ECameraType& CameraType, class AEHCameraActor* Camera) { Cameras.Add(CameraType, Camera); }
	void ActiveCameraShake(bool bActive);

private:
	UPROPERTY()
	TMap<ECameraType, TObjectPtr<class AEHCameraActor>> Cameras;

#pragma endregion

};