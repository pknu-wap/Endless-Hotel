// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Component/EHComponent.h"
#include <CoreMinimal.h>
#include <BedDirectionComponent.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UBedDirectionComponent : public UEHComponent
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Reference

private:
	TWeakObjectPtr<class AEHPlayer> Player;
	TWeakObjectPtr<class UCapsuleComponent> PlayerRoot;
	TWeakObjectPtr<class AEHPlayerController> PC;
	TWeakObjectPtr<class AEHPlayerCameraManager> CameraManager;

#pragma endregion

#pragma region Direction

public:
	void SetPlayerInputAble(bool bAble);
	void ShowEyeEffect(bool bOpen);
	void ShowEyeFastEffect();
	void SyncCameraRotation(bool bOn);

private:
	FTimerHandle ControllerHandle;

#pragma endregion

};