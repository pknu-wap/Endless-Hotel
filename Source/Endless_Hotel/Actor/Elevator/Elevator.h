// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Actor/EHActor.h"
#include <CoreMinimal.h>
#include <Elevator.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AElevator : public AEHActor
{
    GENERATED_BODY()

#pragma region Base

public:
    AElevator(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void BeginPlay() override;

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
    void SetLightOn(bool bIsOn);

protected:
    UPROPERTY(EditAnywhere, Category = "Setting|LightSettings")
    float LightOnIntensity = 100000.f;

    UPROPERTY(EditAnywhere, Category = "Setting|LightSettings")
    float LightOffIntensity = 5000.f;

#pragma endregion

#pragma region Audio

protected:UPROPERTY(VisibleAnywhere, Category = "Audio")
    TObjectPtr<class UAudioComponent> Door_AC;

    UPROPERTY(EditAnywhere, Category = "Audio")
    TObjectPtr<class USoundWave> Sound_DoorMove;

#pragma endregion

#pragma region MovementSettings

public:
    UFUNCTION()
    void MoveDoors(bool bWillOpen);

    UFUNCTION()
    void OnDoorTimelineUpdate(float Alpha);

    UFUNCTION()
    void OnDoorTimelineFinished();

protected:
    void MoveElevator(FVector Start, FVector End, bool bIsStart);

public:
    UPROPERTY(EditAnywhere, Category = "Movement|Elevator")
    FName ElevatorID;

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

private:
    FTimerHandle MoveHandle;
    FVector ReferencePosition;
    FRotator ReferenceRotation;

    bool bIsDoorOpened = false;
    bool bIsDoorMoving = false;

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

protected:
    UPROPERTY(EditAnywhere, Category = "Elevator")
    TObjectPtr<class AElevator_Entrance> LinkedEntrance;

#pragma endregion

#pragma region Wall

protected:
    UPROPERTY(EditAnywhere, Category = "Elevator|Wall")
    TWeakObjectPtr<class AElevator_Wall> ElevatorWall;

#pragma endregion

#pragma region Subsystem

protected:
    void NotifySubsystem();

    UFUNCTION()
    void StartElevator();

protected:
    UPROPERTY(EditAnywhere, Category = "Type")
    bool bIsNormalElevator = true;

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

#pragma region ElevatorFloor

public:
    void DisableElevatorFloor();

#pragma endregion

#pragma region Trigger

public:
    void SetActiveBlockBox(bool bIsActive);

protected:
    UPROPERTY(EditAnywhere, Category = "Elevator|Trigger")
    FVector BlockBoxActiveExtent = FVector(100.f, 32.f, 150.f);

#pragma endregion
};