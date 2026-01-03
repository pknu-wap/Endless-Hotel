// Elevator.h
#pragma once

#include <CoreMinimal.h>
#include "Actor/EHActor.h"
#include "Elevator.generated.h"

#pragma region ForwardDeclarations

class UPointLightComponent;
class UStaticMeshComponent;
class UBoxComponent;
class USceneComponent;
class UTimelineComponent;
class UCurveFloat;
class ACharacter;
class AEHCharacter;
class AElevator_Button;

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API AElevator : public AEHActor
{
	GENERATED_BODY()

#pragma region Base

public:
	AElevator(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

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

#pragma region Buttons

protected:
	UPROPERTY(EditAnywhere, Category = "Button")
	TObjectPtr<AElevator_Button> ElevatorButton;

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
	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC;

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

	TObjectPtr<ACharacter> CachedPlayer;

	bool bIsPlayerInside;


public:
	void MoveDoors(bool isOpening);

	void TryCloseDoorAfterDelay();

	UFUNCTION()
	void OnDoorTimelineUpdate(float Alpha);

	UFUNCTION()
	void OnDoorTimelineFinished();

#pragma endregion

#pragma region ElevatorMovement

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

#pragma endregion

#pragma region Player

protected:
	UPROPERTY(EditAnywhere)
	int16 RotateAngle;

	FTimerHandle RotateHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trigger")
	TSubclassOf<ACharacter> PlayerBPClass;

	UPROPERTY(EditAnywhere, Category = "Position")
	FVector2D PlayerLocationInElevator;

public:
	UPROPERTY(EditAnywhere, Category = "Position")
	FVector PlayerLocationInRoom;

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

#pragma region Rule
	
protected:
	UPROPERTY(EditAnywhere, Category = "Rule")
	TObjectPtr<UStaticMeshComponent> Rule;

#pragma endregion

};