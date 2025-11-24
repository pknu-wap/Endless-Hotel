// Elevator.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API AElevator : public AActor
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
	TObjectPtr<UStaticMeshComponent> CallPanel;

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
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Button")
	TObjectPtr<UStaticMeshComponent> CallDownButtonRing;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Button")
	TObjectPtr<UStaticMeshComponent> CallDownButton;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Button")
	TObjectPtr<UStaticMeshComponent> CallUpButtonRing;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Button")
	TObjectPtr<UStaticMeshComponent> CallUpButton;

#pragma endregion

#pragma region Light

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Light")
	TObjectPtr<UPointLightComponent> ElevatorLight;

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
	// EntranceTrigger
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Trigger")
	TObjectPtr<UBoxComponent> GetInTrigger;

	// InsideTrigger
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Trigger")
	TObjectPtr<UBoxComponent> InsideTrigger;

private:
	UPROPERTY()
	bool bSkipFirstInsideOverlap = false;

protected:
	UFUNCTION()
	void OnEntranceBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEntranceEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnInsideBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

#pragma endregion

#pragma region DoorMovement

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

	bool bIsDoorMoving;
	bool bIsPlayerInside;
	bool bIsDoorOpened;


protected:
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

protected:
	void RotatePlayer();

	void SmoothRotate(FRotator PlayerRotation, FRotator OriginRoatation);

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
};