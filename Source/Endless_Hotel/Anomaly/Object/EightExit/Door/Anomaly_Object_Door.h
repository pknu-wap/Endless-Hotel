// Copyright by 2025-2 WAP Game 2 team

#pragma once

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
	virtual void Reset() override;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "Index")
	int32 DoorIndex = 0;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh_Handle;

	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC_DoorMove;

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

	FTimerHandle HandleShakeHandle;
	FTimerHandle DoorShakeHandle;

	bool bIsFirstShakeSetting = true;

#pragma endregion

#pragma region Open

public:
	void OpenDoor();
	void PlayOpen_Door();

protected:
	UPROPERTY(EditAnywhere, Category = "Anomaly|Sound")
	TObjectPtr<class USoundWave> Sound_DoorOpen;

	bool bOpenTriggered = false;

#pragma endregion

#pragma region Close

public:
	void CloseDoor();
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
	virtual void Interact_Implementation(AEHCharacter* Interacter) override;

#pragma endregion

#pragma region FirstDoorOpen

protected:
	void MoveToHandlePlayer();

	UFUNCTION()
	void OnMoveCompleted();

	UFUNCTION()
	void OnPushMoveStarted();

	UFUNCTION()
	void OnPushMoveCompleted();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StartTransform")
	FTransform TargetPlayerTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StartTransform")
	FTransform PushPlayerTransform;

protected:
	UFUNCTION()
	void DoorRotateStarted();

	UFUNCTION()
	void DoorRotateCompleted();

	UPROPERTY(EditAnywhere, Category = "Door Settings")
	FTransform DoorOpenTransform;

	UPROPERTY(EditAnywhere, Category = "Door Settings")
	float RotationSpeed = 2.0f;

	bool bIsOpening = false;
	FRotator TargetDoorRotation;

protected:
	bool bIsDoorOpened = false;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* ExitTrigger;

	UFUNCTION()
	void OnExitTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void CloseFirstDoor();

#pragma endregion

#pragma region Normal

public:
	void ReadyDoor();
	void ReadyDoorOpened();

#pragma endregion

};