// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Type/Camera/Type_Camera.h"
#include <CoreMinimal.h>
#include <Camera/PlayerCameraManager.h>
#include <EHPlayerCameraManager.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AEHPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Reference

private:
	void SetReference();

private:
	UPROPERTY()
	TWeakObjectPtr<class AEHPlayerController> PC;

#pragma endregion

#pragma region Possess

public:
	void PossessCamera(const ECameraType& CameraType, const float& BlendTime = 0.f);
	void PossessCamera(AActor* CameraOwner, const float& BlendTime = 0.f);

#pragma endregion

#pragma region Camera

public:
	void RegisterCamera(const ECameraType& CameraType, class AEHCameraActor* Camera) { Cameras.Add(CameraType, Camera); }

private:
	UPROPERTY()
	TMap<ECameraType, TObjectPtr<class AEHCameraActor>> Cameras;

#pragma endregion

};