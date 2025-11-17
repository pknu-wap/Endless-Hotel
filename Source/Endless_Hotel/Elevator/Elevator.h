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

#pragma region Trigger

protected:
	// EntranceTrigger
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Trigger")
	TObjectPtr<UBoxComponent> GetInTrigger;

	// InsideTrigger
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Trigger")
	TObjectPtr<UBoxComponent> InsideTrigger;

<<<<<<< HEAD
	// PresenceTrigger
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Trigger")
	TObjectPtr<UBoxComponent> PresenceTrigger;
=======
	// PlayerTrigger
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Elevator|Trigger")
	TSubclassOf<ACharacter> PlayerBPClass;

#pragma endregion

#pragma region TimeLine
>>>>>>> parent of 0cbff4e (Merge remote-tracking branch 'origin/Develop' into origin/Feature/Anomaly)

protected:
	UFUNCTION()
	void OnInsideBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPresenceBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPresenceEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Elevator|Movement|Vertical")
	TObjectPtr<UTimelineComponent> MoveTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Elevator|Movement|Vertical")
	TObjectPtr<UCurveFloat> MoveCurve;

#pragma endregion

#pragma region Params

protected:
<<<<<<< HEAD
=======

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Elevator|Refs")
	AAnomaly_Generator* AnomalyGenerator;
>>>>>>> parent of 0cbff4e (Merge remote-tracking branch 'origin/Develop' into origin/Feature/Anomaly)

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

<<<<<<< HEAD
private:
	FVector LeftDoorClosed, RightDoorClosed;
	FVector LeftDoorOpenPos, RightDoorOpenPos;

	bool bIsDoorMoving;
	bool bIsPlayerInside;
=======
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Movement|Door")
	bool bWaitDoorCloseBeforMove = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Movement|Door")
	bool bMoveAfterClosePending = false;

	// Move Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Movement|Vertical", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MoveDuration = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Movement|Vertical")
	FVector StartPoint = FVector(0.f, 0.f, 0.f);
>>>>>>> parent of 0cbff4e (Merge remote-tracking branch 'origin/Develop' into origin/Feature/Anomaly)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Movement|Vertical")
	FVector LoopPoint = FVector(0.f, 0.f, 500.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Movement|Vertical")
	FVector LoopSpawnPoint = FVector(0.f, 0.f, -500.f);

	// Player Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Trigger", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float DepartureDelay = 3.0f;

	// Delay Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Sequence", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float StartMoveDelay = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Sequence", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float AutoOpenTimeAtReturn = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Sequence", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float AutoCloseDelayAfterExit = 2.0f;

	// Elevator Anomaly Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Type")
	bool bIsNormalElevator = true;

#pragma endregion

#pragma region DoorMovement

protected:
<<<<<<< HEAD
	void MoveDoors(bool isOpening);

	UFUNCTION()
	void OnDoorTimelineUpdate(float Alpha);

	UFUNCTION()
	void OnDoorTimelineFinished();
=======
	UFUNCTION(BlueprintCallable, Category = "Elevator|Movement|Door")
	void OpenDoors();

	UFUNCTION(BlueprintCallable, Category = "Elevator|Movement|Door")
	void CloseDoors();

	UFUNCTION() void OnDoorTimelineUpdate(float Alpha);
	UFUNCTION() void OnDoorTimelineFinished();
>>>>>>> parent of 0cbff4e (Merge remote-tracking branch 'origin/Develop' into origin/Feature/Anomaly)

#pragma endregion

#pragma region ElevatorMovement

protected:
<<<<<<< HEAD
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
=======
	UFUNCTION(BlueprintCallable, Category = "Elevator|Movement|Vertical")
	void MoveUp();

	UFUNCTION(BlueprintCallable, Category = "Elevator|Movement|Vertical")
	void MoveDown();

	UFUNCTION() void OnMoveTimelineUpdate(float Alpha);
	UFUNCTION() void OnMoveTimelineFinished();

	UFUNCTION() void PerformLoopTeleport();

	UFUNCTION()
	void OnInsideBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
>>>>>>> parent of 0cbff4e (Merge remote-tracking branch 'origin/Develop' into origin/Feature/Anomaly)

	UFUNCTION()
	void OnInsideEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

#pragma endregion

#pragma region Internal

	private:
		// Door Internal
		FVector LeftDoorClosed, RightDoorClosed;
		FVector LeftDoorOpenPos, RightDoorOpenPos;

<<<<<<< HEAD
	FTimerHandle RotateHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trigger")
	TSubclassOf<ACharacter> PlayerBPClass;

protected:
	void RotatePlayer();
=======
		bool bWantOpen = false;
		bool bDoorOpen = false;

		FTimerHandle DoorOpenTimerHandle;
		FTimerHandle DoorCloseTimerHandle;

		// Move Internal
		bool bPlayerOnboard = false;
		bool bIsMoving = false;

		FTimerHandle DepartuerTImerHandle;

		FTimerHandle StartMoveTimer;
		FTimerHandle AutoOpenTimer;
		FTimerHandle AutoCloseTimer;

		// Move Manage (0: Start -> Loop, 1: LoopSpawn -> Start)
		int32 MovePhase = 0;

		FVector OrigStartPoint;
		FVector OrigLoopPoint;

		bool bSequenceArmed = false;

		// SubSystem Internal
		bool bChoiceSentThisRide = false;
		void NotifySubsystemElevatorChoice();

		// Player check helper
		bool bRideCompleted = false;
		bool bSpawnSentThisStop = false;

		bool IsMyPlayer(AActor* Other) const;

#pragma endregion

#pragma region PlayerMoveControl
>>>>>>> parent of 0cbff4e (Merge remote-tracking branch 'origin/Develop' into origin/Feature/Anomaly)

	void SmoothRotate(FRotator PlayerRotation, FRotator OriginRoatation);

private:
	void SetPlayerInputEnabled(bool bEnable);

#pragma endregion
<<<<<<< HEAD

#pragma region Subsystem

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type")
	bool bIsNormalElevator = true;

private:
	bool bChoiceSentThisRide = false;

private:
	void NotifySubsystemElevatorChoice();

#pragma endregion
=======
>>>>>>> parent of 0cbff4e (Merge remote-tracking branch 'origin/Develop' into origin/Feature/Anomaly)
};