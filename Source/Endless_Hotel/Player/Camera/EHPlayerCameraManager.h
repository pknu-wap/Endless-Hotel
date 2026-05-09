// Copyright by 2026-1 WAP Game 2 team

#pragma once

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
	void PossessCamera(const FName& CameraTag, const float& BlendTime);

#pragma endregion

#pragma region Camera

public:
	void RegisterCamera(const FName& CameraTag, class AEHCameraActor* Camera) { Cameras.FindOrAdd(CameraTag, Camera); }

private:
	UPROPERTY()
	TMap<FName, TObjectPtr<class AEHCameraActor>> Cameras

#pragma endregion

};