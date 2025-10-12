// Elevator.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Elevator.generated.h"

// Forward Declarations
class UPointLightComponent;
class UStaticMeshComponent;
class UBoxComponent;
class USceneComponent;
class UTimelineComponent;
class UCurveFloat;
class ACharacter;

UCLASS()
class ENDLESS_HOTEL_API AElevator : public AActor
{
	GENERATED_BODY()
#pragma region Base

public:
	AElevator(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

	// ===== Components =====
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Elevator")
	TObjectPtr<USceneComponent> ElevatorSceneRoot;
#pragma endregion

#pragma region Frames

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Elevator|Frame")
	TObjectPtr<UStaticMeshComponent> Exterior_Structure;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Elevator|Frame")
	TObjectPtr<UStaticMeshComponent> CallPanel;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Elevator|Frame")
	TObjectPtr<UStaticMeshComponent> Entrance;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Elevator|Frame")
	TObjectPtr<UStaticMeshComponent> Car;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Elevator|Doors")
	TObjectPtr<UStaticMeshComponent> LeftDoor;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Elevator|Doors")
	TObjectPtr<UStaticMeshComponent> RightDoor;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Elevator|Doors")
	TObjectPtr<UStaticMeshComponent> RightGlass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Elevator|Doors")
	TObjectPtr<UStaticMeshComponent> LeftGlass;

#pragma endregion

#pragma region Buttons

protected:
	// Buttons
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Elevator|Button")
	TObjectPtr<UStaticMeshComponent> CallDownButtonRing;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Elevator|Button")
	TObjectPtr<UStaticMeshComponent> CallDownButton;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Elevator|Button")
	TObjectPtr<UStaticMeshComponent> CallUpButtonRing;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Elevator|Button")
	TObjectPtr<UStaticMeshComponent> CallUpButton;

#pragma endregion

#pragma region Light

protected:
	// Light
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Elevator|Light")
	TObjectPtr<UPointLightComponent> ElevatorLight;

#pragma endregion

#pragma region Trigger

protected:
	// EntranceTrigger
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Elevator|Trigger")
	TObjectPtr<UBoxComponent> GetInTrigger;

	// InsideTrigger
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Elevator|Trigger")
	TObjectPtr<UBoxComponent> InsideTrigger;

	// PlayerTrigger
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Elevator|Trigger")
	TSubclassOf<ACharacter> PlayerBPClass;

#pragma endregion

#pragma region TimeLine

protected:
	// Timeline
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Elevator|Movement|Door")
	TObjectPtr<UTimelineComponent> DoorTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Elevator|Movement|Door")
	TObjectPtr<UCurveFloat> DoorCurve;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Elevator|Movement|Vertical")
	TObjectPtr<UTimelineComponent> MoveTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Elevator|Movement|Vertical")
	TObjectPtr<UCurveFloat> MoveCurve;

#pragma endregion

#pragma region Params

protected:
	// Door Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Movement|Door", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float DoorDuration = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Movement|Door")
	float DoorGap = 40.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Movement|Door")
	bool bSlideOnX = true;

	// Move Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Movement|Vertical", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MoveDuration = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator|Movement|Vertical")
	FVector StartPoint = FVector(0.f, 0.f, 0.f);

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
	UFUNCTION(BlueprintCallable, Category = "Elevator|Movement|Door")
	void OpenDoors();

	UFUNCTION(BlueprintCallable, Category = "Elevator|Movement|Door")
	void CloseDoors();

	UFUNCTION() void OnDoorTimelineUpdate(float Alpha);
	UFUNCTION() void OnDoorTimelineFinished();

	// Overlap
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

#pragma endregion

#pragma region ElevatorMovement

protected:
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

	UFUNCTION()
	void OnInsideEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

#pragma endregion

#pragma region Internal

	private:
		// Door Internal
		FVector LeftDoorClosed, RightDoorClosed;
		FVector LeftDoorOpenPos, RightDoorOpenPos;

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
		void NotifySubsystemSpawnNextAnomaly();

		// Player check helper
		bool bRideCompleted = false;
		bool bSpawnSentThisStop = false;

		bool IsMyPlayer(AActor* Other) const;

#pragma endregion

};