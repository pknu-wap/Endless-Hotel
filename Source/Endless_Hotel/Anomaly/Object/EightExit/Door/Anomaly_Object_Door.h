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

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	int32 DoorIndex = 0;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh_Handle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UAudioComponent> AC_Effect;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UAudioComponent> AC_Voice;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UAudioComponent> AC_DoorMove;

#pragma endregion

#pragma region Shake

public:
	void DoorShaking();

protected:
	void PlayShake_Handle();
	void PlayShake_Door();

	void Timer_Handle();
	void Timer_Door();

	UFUNCTION()
	void ShakeDoor(float Value);

	UFUNCTION()
	void ShakeHandle(float Value);

protected:
	UPROPERTY()
	TObjectPtr<class UTimelineComponent> Timeline_Door;

	UPROPERTY()
	TObjectPtr<class UTimelineComponent> Timeline_Handle;

	UPROPERTY(EditAnywhere, Category = "Anomaly|Time")
	TObjectPtr<UCurveFloat> Curve_Door;

	UPROPERTY(EditAnywhere, Category = "Anomaly|Time")
	TObjectPtr<UCurveFloat> Curve_Handle;

	FVector Door_Origin;
	FVector Handle_Origin;

	FTimerHandle HandleHandle;
	FTimerHandle DoorHandle;

	const uint8 MaxShakeCount_Handle = 29;
	uint8 ShakeCount_Handle = 0;

	const uint8 MaxShakeCount_Door = 4;
	uint8 ShakeCount_Door = 0;

	UPROPERTY(EditAnywhere, Category = "Anomaly|Sound")
	TObjectPtr<class USoundWave> Sound_DoorShake;

	UPROPERTY(EditAnywhere, Category = "Anomaly|Sound")
	TArray<TObjectPtr<class USoundWave>> Sounds_Voice;

#pragma endregion

#pragma region Open

public:
	void OpenDoor();
	void PlayOpen_Door();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Sound")
	TObjectPtr<class USoundWave> Sound_DoorOpen;

	bool bOpenTriggered = false;

#pragma endregion

#pragma region Close
public:
	void CloseDoor();
	void PlayClose_Door();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Sound")
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Sound")
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
	FTransform DoorInitialTransform;

	UPROPERTY(EditAnywhere, Category = "Door Settings")
	float RotationSpeed = 2.0f;

	bool bIsOpening = false;
	FRotator TargetDoorRotation;

protected:
	bool bIsDoorOpened = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite , Category = "Components")
	class UBoxComponent* ExitTrigger;

	UFUNCTION()
	void OnExitTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void CloseFirstDoor();

#pragma endregion

};