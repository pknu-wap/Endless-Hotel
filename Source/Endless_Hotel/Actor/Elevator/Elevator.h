// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Actor/EHActor.h"
#include <CoreMinimal.h>
#include <Elevator.generated.h>

#pragma region Declare

class UElevatorManagerSubsystem;
class UElevatorCinematicComponent;

enum class EMapDataLayer : uint8;
enum class EElevatorMoveKind : uint8
{
    None,
    Arrival,
    Departure
};

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API AElevator : public AEHActor
{
    GENERATED_BODY()

#pragma region Base

public:
    AElevator(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void PostInitializeComponents() override;
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    UPROPERTY(VisibleAnywhere, Category = "Frame")
    TObjectPtr<UStaticMeshComponent> Exterior_Structure;

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
    TObjectPtr<class UBoxComponent> TriggerBlockBox;

    UPROPERTY(EditAnywhere, Category = "Teleport")
    TObjectPtr<USceneComponent> TeleportAnchor;

#pragma endregion

#pragma region LightSettings

public:
    void SetLightOn(bool bIsOn) const;

protected:
    UPROPERTY(EditAnywhere, Category = "Setting|LightSettings")
    float LightOnIntensity = 100000.f;

    UPROPERTY(EditAnywhere, Category = "Setting|LightSettings")
    float LightOffIntensity = 5000.f;

#pragma endregion

#pragma region Audio

protected:
    UPROPERTY(VisibleAnywhere, Category = "Audio")
    TObjectPtr<UAudioComponent> Door_AC;

    UPROPERTY(VisibleAnywhere, Category = "Audio")
    TObjectPtr<UAudioComponent> Move_AC;

#pragma endregion

#pragma region MovementSettings

public:
    UPROPERTY(EditAnywhere, Category = "Movement|Elevator")
    FName ElevatorID;

    UPROPERTY(VisibleAnywhere, Category = "Movement")
    TObjectPtr<class UElevatorMoveComponent> MoveComp;

protected:
    UPROPERTY(VisibleAnywhere, Category = "Movement")
    TObjectPtr<class UTimelineComponent> MoveTimeline;

    UPROPERTY(EditAnywhere, Category = "Movement|Elevator")
    TObjectPtr<UCurveFloat> MoveCurve;

private:
    void PlayArrivalSequence();
    void PlayDepartureSequence();
    void HandleMoveFinished();

    EElevatorMoveKind CurrentMove = EElevatorMoveKind::None;
    FTimerHandle MoveHandle;

#pragma endregion

#pragma region Door
    
public:
    UFUNCTION()
    void MoveDoors(bool bWillOpen) const;
    
public:
    UPROPERTY(VisibleAnywhere, Category = "Door")
    TObjectPtr<class UElevatorDoorComponent> DoorComp;
    
protected:
    UPROPERTY(VisibleAnywhere, Category = "Movement")
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
    
#pragma endregion
    
#pragma region Button

public:
    UFUNCTION()
    void OnButtonClicked(bool bIsOpening);

protected:
    UPROPERTY(EditAnywhere, Category = "Elevator|Button")
    TWeakObjectPtr<class AElevator_Button> InsideButton;

    UPROPERTY(EditAnywhere, Category = "Elevator|Button")
    TWeakObjectPtr<class AElevator_Button> EntranceButton;

#pragma endregion

#pragma region Entrance

public:
    UPROPERTY(EditAnywhere, Category = "Elevator")
    TWeakObjectPtr<class AElevator_Entrance> LinkedEntrance;

#pragma endregion

#pragma region Wall

public:
    UPROPERTY(EditAnywhere, Category = "Elevator|Wall")
    TWeakObjectPtr<class AElevator_Wall> ElevatorUnderWall;

    UPROPERTY(EditAnywhere, Category = "Elevator|Wall")
    TWeakObjectPtr<class AElevator_Wall> ElevatorOverWall;

#pragma endregion

#pragma region Subsystem

public:
    void StartElevator();
    
private:
    void RequestAnomalyVerdict() const;
    void ResetState() const;
    void PrepareAsTarget(const UElevatorManagerSubsystem& Sub);
    void PrepareAsNonTarget() const;

public:
    UPROPERTY(VisibleAnywhere, Category = "Passenger")
    TObjectPtr<class UElevatorPassengerComponent> PassengerComp;

    UPROPERTY(VisibleAnywhere, Category = "Verdict")
    TObjectPtr<class UElevatorGameFlowComponent> VerdictComp;
    
private:
    FTimerHandle MoveStartHandle;

#pragma endregion

#pragma region Position

public:
    UPROPERTY(EditAnywhere, Category = "Move|Elevator")
    FVector StartPos;

    UPROPERTY(EditAnywhere, Category = "Move|Elevator")
    FVector MapPos;

    UPROPERTY(EditAnywhere, Category = "Move|Elevator")
    FVector EndPos;
    
    UPROPERTY(EditAnywhere, Category = "Move|Elevator")
    FVector RideStartPos;

    UPROPERTY(EditAnywhere, Category = "Move|Elevator")
    FVector RideEndPos;

    UPROPERTY(EditAnywhere, Category = "Move|Elevator")
    FVector StandardPos;

#pragma endregion

#pragma region Anomaly

public:
    void DisableElevatorFloor();
    void DisableElevator() const;

#pragma endregion

#pragma region Trigger

protected:
    UPROPERTY(EditAnywhere, Category = "Elevator|Trigger")
    FVector BlockBoxActiveExtent = FVector(100.f, 32.f, 150.f);

#pragma endregion
    
#pragma region Cinematic

protected:
    UPROPERTY(EditAnywhere, Category = "Cinematic")
    bool bIsLobbyElevator = false;
    
private:
    bool bIsRiding = false;

#pragma endregion
    
};