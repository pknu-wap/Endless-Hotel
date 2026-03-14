// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Actor/EHActor.h"
#include <CoreMinimal.h>
#include <Elevator.generated.h>

UENUM(BlueprintType)
enum class EElevatorState : uint8
{
    Idle,
    DoorMoving,
    Moving,
    Finished
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FElevatorDelegate, bool, bIsStart);

UCLASS()
class ENDLESS_HOTEL_API AElevator : public AEHActor
{
    GENERATED_BODY()

#pragma region Base

public:
    AElevator(const FObjectInitializer& ObjectInitializer);
    static FElevatorDelegate ElevatorDelegate;

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnInsideBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnInsideEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
    UPROPERTY(VisibleAnywhere, Category = "Frame")
    TObjectPtr<UStaticMeshComponent> Exterior_Structure;

    UPROPERTY(VisibleAnywhere, Category = "Frame")
    TObjectPtr<UStaticMeshComponent> Entrance;

    UPROPERTY(VisibleAnywhere, Category = "Frame")
    TObjectPtr<UStaticMeshComponent> Car;

    UPROPERTY(VisibleAnywhere, Category = "Doors")
    TObjectPtr<UStaticMeshComponent> LeftDoor;

    UPROPERTY(VisibleAnywhere, Category = "Doors")
    TObjectPtr<UStaticMeshComponent> RightDoor;

    UPROPERTY(VisibleAnywhere, Category = "Doors")
    TObjectPtr<UStaticMeshComponent> RightGlass;

    UPROPERTY(VisibleAnywhere, Category = "Doors")
    TObjectPtr<UStaticMeshComponent> LeftGlass;

    UPROPERTY(EditAnywhere, Category = "Floor")
    TObjectPtr<UStaticMeshComponent> Floor;

    UPROPERTY(VisibleAnywhere, Category = "Light")
    TObjectPtr<class UPointLightComponent> ElevatorLight;

    UPROPERTY(VisibleAnywhere, Category = "Trigger")
    TObjectPtr<class UBoxComponent> InsideTrigger;

    UPROPERTY(VisibleAnywhere, Category = "Trigger")
    TObjectPtr<UStaticMeshComponent> TriggerBlockBox;

    UPROPERTY(VisibleAnywhere, Category = "UI")
    TObjectPtr<UStaticMeshComponent> StickerPannel;

private:
    EElevatorState CurrentState = EElevatorState::Idle;

#pragma endregion

#pragma region LightSettings

protected:
    UPROPERTY(EditAnywhere, Category = "Setting|LightSettings")
    float LightOnIntensity = 100000.f;

    UPROPERTY(EditAnywhere, Category = "Setting|LightSettings")
    float LightOffIntensity = 5000.f;

#pragma endregion

#pragma region Audio

protected:
    UPROPERTY(VisibleAnywhere, Category = "Audio")
    TObjectPtr<class UAudioComponent> Elevator_AC;

    UPROPERTY(VisibleAnywhere, Category = "Audio")
    TObjectPtr<class UAudioComponent> Door_AC;

    UPROPERTY(EditAnywhere, Category = "Audio")
    TObjectPtr<class USoundWave> Sound_DoorMove;

    UPROPERTY(EditAnywhere, Category = "Audio")
    TObjectPtr<class USoundWave> Sound_ElevatorMove;

#pragma endregion

#pragma region MovementSettings

public:
    void MoveDoors(bool bIsOpening);

    UFUNCTION()
    void OnDoorTimelineUpdate(float Alpha);

    UFUNCTION()
    void OnDoorTimelineFinished();

protected:
    void ElevatorMove(FVector Start, FVector End, bool bIsStart);
    void ExecuteElevatorRide();

    UFUNCTION()
    void OpenDoorAfterMove();

    UFUNCTION()
    void BroadcastElevatorFinished();

protected:
    UPROPERTY(EditAnywhere, Category = "Movement")
    TObjectPtr<class UTimelineComponent> DoorTimeline;

    UPROPERTY(EditAnywhere, Category = "Movement|Door")
    TObjectPtr<UCurveFloat> DoorCurve;

    UPROPERTY(EditAnywhere, Category = "Movement|Door")
    float DoorDuration = 1.0f;

    UPROPERTY(EditAnywhere, Category = "Movement|Door|Closed")
    FVector LeftDoorClosed;

    UPROPERTY(EditAnywhere, Category = "Movement|Door|Closed")
    FVector RightDoorClosed;

    UPROPERTY(EditAnywhere, Category = "Movement|Door|Opened")
    FVector LeftDoorOpenPos;

    UPROPERTY(EditAnywhere, Category = "Movement|Door|Opened")
    FVector RightDoorOpenPos;

    UPROPERTY(EditAnywhere, Category = "Movement|Elevator")
    float ElevatorMoveDuration = 3.0f;

    UPROPERTY(EditAnywhere, Category = "Movement|Elevator")
    bool bIsMapStartElevator;

private:
    FTimerHandle MoveHandle;

    FTimerHandle BoardingCloseTimerHandle;

    bool bShouldMoveAfterClose = false;

    bool bIsDoorOpened = false;

    bool bIsDoorMoving = false;

#pragma endregion

#pragma region Player

protected:
    void SetPlayerInputEnabled(bool bEnable);

    void RotatePlayer();

    void SmoothRotate(FRotator TargetRotation);

    void TakePlayer();

protected:
    UPROPERTY(EditAnywhere, Category = "Player")
    FRotator RotateAngle;

private:
    FTimerHandle RotateHandle;

    bool bIsPlayerInside = false;

#pragma endregion

#pragma region Button

public:
    UFUNCTION()
    void OnButtonClicked();

protected:
    UPROPERTY(EditAnywhere, Category = "Elevator|Button")
    TObjectPtr<class AElevator_Button> AttachedButton;

#pragma endregion

#pragma region Subsystem

protected:
    void NotifySubsystemElevatorChoice();

protected:
    UPROPERTY(EditAnywhere, Category = "Type")
    bool bIsNormalElevator = true;

private:
    bool bChoiceSentThisRide = false;

#pragma endregion

#pragma region Position

public:
    UPROPERTY(EditAnywhere, Category = "Position|Elevator")
    FVector StartPos;

    UPROPERTY(EditAnywhere, Category = "Position|Elevator")
    FVector MapPos;

    UPROPERTY(EditAnywhere, Category = "Position|Elevator")
    FVector EndPos;

#pragma endregion

#pragma region Reset

    void EnableFloor();

#pragma endregion


#pragma region Anomaly

public:
    void DisableFloor();

#pragma endregion

};