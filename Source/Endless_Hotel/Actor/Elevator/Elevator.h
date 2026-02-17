// Elevator.h
#pragma once

#include "Actor/EHActor.h"
#include <CoreMinimal.h>
#include <Delegates/DelegateCombinations.h>
#include <Elevator.generated.h>

#pragma region ForwardDeclarations

class UPointLightComponent;
class UStaticMeshComponent;
class UBoxComponent;
class USceneComponent;
class UTimelineComponent;
class UCurveFloat;
class AElevator_Button;

#pragma endregion

#pragma region Declare

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FElevatorDelegate, bool, bIsStart);

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API AElevator : public AEHActor
{
	GENERATED_BODY()

#pragma region Base

public:
	AElevator(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Elevator")
	TObjectPtr<USceneComponent> ElevatorSceneRoot;

#pragma endregion

#pragma region Frames

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Frame")
	TObjectPtr<UStaticMeshComponent> Exterior_Structure;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Frame")
	TObjectPtr<UStaticMeshComponent> Entrance;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Frame")
	TObjectPtr<UStaticMeshComponent> Car;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Doors")
	TObjectPtr<UStaticMeshComponent> LeftDoor;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Doors")
	TObjectPtr<UStaticMeshComponent> RightDoor;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Doors")
	TObjectPtr<UStaticMeshComponent> RightGlass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Doors")
	TObjectPtr<UStaticMeshComponent> LeftGlass;

#pragma endregion

#pragma region Light

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Light")
	TObjectPtr<UPointLightComponent> ElevatorLight;

	const float LightOnIntensity = 100000.f;
	const float LightOffIntensity = 5000.f;

#pragma endregion

#pragma region Sound

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> Elevator_AC;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> Door_AC;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> Sound_DoorMove;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> Sound_ElevatorMove;

#pragma endregion

#pragma region Trigger

protected:
	// InsideTrigger
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Trigger")
	TObjectPtr<UBoxComponent> InsideTrigger;

protected:
	UFUNCTION()
	void OnInsideBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnInsideEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

#pragma endregion

#pragma region DoorMovement

public:
	void MoveDoors(bool isOpening);

	void TryCloseDoorAfterDelay();

	UFUNCTION()
	void OnDoorTimelineUpdate(float Alpha);

	UFUNCTION()
	void OnDoorTimelineFinished();

protected:
	UFUNCTION()
	void OpenDoorAfterMove();

public:
	bool bIsDoorMoving;
	bool bIsDoorOpened;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement|Door")
	TObjectPtr<UTimelineComponent> DoorTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement|Door")
	TObjectPtr<UCurveFloat> DoorCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Door", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float DoorDuration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Door")
	float DoorGap = 40.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Door")
	bool bSlideOnX = true;

private:
	FVector LeftDoorClosed, RightDoorClosed;
	FVector LeftDoorOpenPos, RightDoorOpenPos;

	FTimerHandle DoorCloseTimerHandle;

	bool bIsPlayerInside;

#pragma endregion

#pragma region ElevatorMovement

public:
	static FElevatorDelegate ElevatorDelegate;

	UPROPERTY(EditAnywhere, Category = "Movement|Elevator")
	bool bIsMapStartElevator;

protected:
	UPROPERTY(EditAnywhere, Category = "Movement|Elevator")
	FVector StartPos;

	UPROPERTY(EditAnywhere, Category = "Movement|Elevator")
	FVector MapPos;

	UPROPERTY(EditAnywhere, Category = "Movement|Elevator")
	FVector EndPos;

	UPROPERTY(EditAnywhere, Category = "Movement|Elevator")
	float ElevatorMoveDuration = 3.0f;

public:
	void CallElevator();

protected:
	void ElevatorMove(FVector Start, FVector End, bool bIsStart);

private:
	FTimerHandle MoveHandle;

#pragma endregion

#pragma region Player

protected:
	UPROPERTY(EditAnywhere)
	FRotator RotateAngle;

	FTimerHandle RotateHandle;

	UPROPERTY(EditAnywhere, Category = "Position")
	FVector2D PlayerLocationInElevator;

protected:
	void RotatePlayer();
	void SmoothRotate(FRotator OriginRoatation);
	void TakePlayer();

private:
	void SetPlayerInputEnabled(bool bEnable);

#pragma endregion

#pragma region Subsystem

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type")
	bool bIsNormalElevator = true;

private:
	bool bChoiceSentThisRide = false;

private:
	void NotifySubsystemElevatorChoice();

#pragma endregion

#pragma region UI

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TObjectPtr<class UStaticMeshComponent> StickerPannel;

#pragma endregion


};