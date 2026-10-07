// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Components/ActorComponent.h>
#include "ElevatorCinematicComponent.generated.h"

#pragma region Declare

class USceneComponent;
class UAudioComponent;
class UCurveFloat;
class UTimelineComponent;
class UElevatorDoorComponent;
class UElevatorPassengerComponent;
enum class EMapDataLayer : uint8;

UENUM(BlueprintType)
enum class EElevatorCinematicRole : uint8
{
    Lobby,
    Hallway
};

#pragma endregion

UCLASS(ClassGroup = (Elevator), meta = (BlueprintSpawnableComponent))
class ENDLESS_HOTEL_API UElevatorCinematicComponent : public UActorComponent
{
    GENERATED_BODY()

#pragma region Base

public:
    void Init(USceneComponent* InTarget, UElevatorDoorComponent* InDoor,
        UElevatorPassengerComponent* InPassenger, UAudioComponent* InMoveAC,
        UTimelineComponent* InTimeline);

protected:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditAnywhere, Category = "Cinematic")
    EElevatorCinematicRole Role = EElevatorCinematicRole::Hallway;

private:
    UPROPERTY(Transient)
    TObjectPtr<USceneComponent> Target;

    UPROPERTY(Transient)
    TObjectPtr<UElevatorDoorComponent> Door;

    UPROPERTY(Transient)
    TObjectPtr<UElevatorPassengerComponent> Passenger;

    UPROPERTY(Transient)
    TObjectPtr<UAudioComponent> MoveAC;

    UPROPERTY(Transient)
    TObjectPtr<UTimelineComponent> RideTimeline;

#pragma endregion

#pragma region Ride

public:
    bool PrepareRide() const;
    void BeginRide();
    void CancelRide();

private:
    bool IsHallwayRideActive() const;
    void StartSegment() const;
    void FinishRide() const;

    FVector GetRideStart() const { return BaseLocation + RideStartOffset; }
    FVector GetRideEnd() const;

    UFUNCTION()
    void HandleTimelineUpdate(float Alpha) const;

    UFUNCTION()
    void HandleTimelineFinished();

protected:
    UPROPERTY(EditAnywhere, Category = "Cinematic|Hallway")
    TObjectPtr<UCurveFloat> RideCurve;

    UPROPERTY(EditAnywhere, Category = "Cinematic|Hallway")
    FVector RideStartOffset;

    UPROPERTY(EditAnywhere, Category = "Cinematic|Hallway")
    FVector RideEndOffset;

    UPROPERTY(EditAnywhere, Category = "Cinematic|Hallway")
    int32 RideLoopCount = 7;

    UPROPERTY(EditAnywhere, Category = "Cinematic|Hallway")
    float SegmentDuration = 3.f;
    
    UPROPERTY(EditAnywhere, Category = "Cinematic|Hallway")
    FVector LastSegmentOffset;

private:
    FVector BaseLocation = FVector::ZeroVector;
    int32 LoopsLeft = 0;

#pragma endregion

#pragma region Handoff

public:
    bool HandleDepartureFinished();

private:
    void OnLayerReady() const;

protected:
    UPROPERTY(EditAnywhere, Category = "Cinematic|Lobby")
    FName NextElevatorID;

    UPROPERTY(EditAnywhere, Category = "Cinematic|Lobby")
    EMapDataLayer NextLayer;

#pragma endregion
};