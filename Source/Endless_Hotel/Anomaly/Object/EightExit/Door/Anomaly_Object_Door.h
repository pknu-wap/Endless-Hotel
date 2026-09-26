// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/Save/Type_Save.h"
#include "Anomaly/Object/EightExit/Anomaly_Object_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Door.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Door : public AAnomaly_Object_EightExit
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_Door(const FObjectInitializer& ObjectInitializer);
	virtual void InitializeOnAnomalySpawned() override;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "Index")
	int32 DoorIndex = 0;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh_Handle;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh_Handle2;

	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC_DoorMove;

#pragma endregion

#pragma region Progression

private:
	void OnChangedProgression(EGameProgression Target);

#pragma endregion

#pragma region Shake

public:
	void StartShaking();

private:
	UFUNCTION()
	void ShakeDoor(float Value);

	UFUNCTION()
	void ShakeHandle(float Value);

	UFUNCTION()
	void ShakeDoorEnd();

	UFUNCTION()
	void ShakeHandleEnd();

protected:
	UPROPERTY(EditAnywhere, Category = "Shake")
	TObjectPtr<UCurveFloat> CV_Door;

	UPROPERTY(EditAnywhere, Category = "Shake")
	TObjectPtr<UCurveFloat> CV_Handle;

	UPROPERTY(EditAnywhere, Category = "Shake")
	TArray<TObjectPtr<USoundWave>> SW_Voice;

private:
	UPROPERTY()
	TObjectPtr<class UTimelineComponent> TL_Door;

	UPROPERTY()
	TObjectPtr<class UTimelineComponent> TL_Handle;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> AC_Shake;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> AC_Voice;

	FVector DoorOrigin;
	FVector HandleOrigin;

	const uint8 MaxHandleShake = 30;
	uint8 CurrentHandleShake = 0;

	const uint8 MaxDoorShake = 4;
	uint8 CurrentDoorShake = 0;

	FTimerHandle StartHandle;
	FTimerHandle HandleShakeHandle;
	FTimerHandle DoorShakeHandle;

	bool bIsFirstShakeSetting = true;

#pragma endregion

#pragma region Open

public:
	UFUNCTION()
	void OpenDoor();

protected:
	void PlayOpen_Door();

protected:
	UPROPERTY(EditAnywhere, Category = "Anomaly|Sound")
	TObjectPtr<class USoundWave> Sound_DoorOpen;

	bool bOpenTriggered = false;

#pragma endregion

#pragma region Close

public:
	void CloseDoor();

protected:
	void PlayClose_Door();

protected:

	UPROPERTY(EditAnywhere, Category = "Anomaly|Sound")
	TObjectPtr<class USoundWave> Sound_DoorClose;

	bool bCloseTriggered = false;

#pragma endregion

#pragma region Rotate

protected:
	void StartRotateOpen();
	void StartRotateClose();

	UFUNCTION()
	void UpdateRotateOpen(float Value);

	UFUNCTION()
	void UpdateRotateClose(float Value);

	UFUNCTION()
	void FinishRotateClose();

protected:
	UPROPERTY()
	TObjectPtr<class UTimelineComponent> Timeline_Open;

	UPROPERTY()
	TObjectPtr<class UTimelineComponent> Timeline_Close;

	UPROPERTY(EditAnywhere, Category = "Anomaly|Time")
	TObjectPtr<UCurveFloat> Curve_Open;

	UPROPERTY(EditAnywhere, Category = "Anomaly|Time")
	TObjectPtr<UCurveFloat> Curve_Close;

protected:
	float OpenYaw = 0.f;
	float CloseYaw = 0.f;
	float BaseYaw = 0.f;

#pragma endregion

#pragma region Interact

protected:
	UPROPERTY(EditAnywhere, Category = "Anomaly|Sound")
	TObjectPtr<class USoundWave> Sound_HandleTwist;

	void PlayHandleTwistSound();

public:
	virtual void Interact(class AEHCharacter* Interacter) override;

#pragma endregion

#pragma region FirstDoorOpen

private:
	void MoveToHandlePlayer();

	UFUNCTION()
	void OnMoveCompleted();

	UFUNCTION()
	void OnPushMoveStarted();

	UFUNCTION()
	void OnPushMoveCompleted();

	void ResetDoorState();

	void MoveToHandleKey();

	UFUNCTION()
	void RotateKey();

private:
	UPROPERTY(EditAnywhere, Category = "StartTransform")
	FTransform TargetPlayerTransform;

	UPROPERTY(EditAnywhere, Category = "StartTransform")
	FTransform PushPlayerTransform;

	UPROPERTY(EditAnywhere, Category = "Door Settings")
	FTransform DoorOpenTransform;

	UPROPERTY(EditAnywhere, Category = "Door Settings")
	float RotationSpeed = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Key")
	TSubclassOf<class AStaticMeshActor> KeyClass;

	UPROPERTY()
	TObjectPtr<class AStaticMeshActor> KeyActor;

	FRotator TargetDoorRotation;

#pragma endregion

//#pragma region GhostHand
//
//public:
//	void PlayHandOpen();
//	void PlayHandClose();
//
//private:
//	void SpawnGhostHand();
//
//protected:
//	UPROPERTY(EditAnywhere, Category = "Anomaly|GhostHand")
//	TObjectPtr<class USkeletalMesh> GhostHandMesh;
//
//	UPROPERTY()
//	TObjectPtr<class ASkeletalMeshActor> SpawnedGhostHandActor;
//
//	UPROPERTY()
//	TObjectPtr<USkeletalMeshComponent> SKM_GhostHand;
//
//	UPROPERTY(EditAnywhere, Category = "Anomaly|GhostHand")
//	TObjectPtr<class UAnimationAsset> Anim_HandOpen;
//
//	UPROPERTY(EditAnywhere, Category = "Anomaly|GhostHand")
//	TObjectPtr<class UAnimationAsset> Anim_HandClose;
//
//	UPROPERTY(EditAnywhere, Category = "Anomaly|GhostHand")
//	FName GhostHandSocketName = TEXT("GhostHandSocket");
//
//#pragma endregion

#pragma region Light Channel

private:
	void SetLight(bool bIsStartFloor);

#pragma endregion

};