// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Component/EHComponent.h"
#include <CoreMinimal.h>
#include <BedDirectionComponent.generated.h>

#pragma region Declare

USTRUCT(BlueprintType)
struct FBedDirectionInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Info")
	FTransform TargetTrans;

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float Delay;

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float Duration;
};

#pragma endregion

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
	void ShowDirection(TArray<FBedDirectionInfo> Infos);
	void ShowEyeEffect(bool bOpen);
	void AdjustControllerRotation(const FRotator& TargetRotation, float Duration);

private:
	FTimerHandle ControllerHandle;

	FRotator StartControllerRot;
	FRotator TargetControllerRot;

	float ControllerElapsed = 0.f;
	float ControllerDuration = 0.f;

#pragma endregion

};