// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Component/EHComponent.h"
#include <CoreMinimal.h>
#include <ElevatorMoveComponent.generated.h>

#pragma region Declare

class UAudioComponent;
class UTimelineComponent;
class UCurveFloat;

struct FElevatorMoveConfig
{
    UCurveFloat* Curve = nullptr;
    FVector StandardPos = FVector::ZeroVector;
    FVector StartPos = FVector::ZeroVector;
    FVector MapPos = FVector::ZeroVector;
    FVector EndPos = FVector::ZeroVector;
};

#pragma endregion

UCLASS(ClassGroup = (Elevator), meta = (BlueprintSpawnableComponent))
class ENDLESS_HOTEL_API UElevatorMoveComponent : public UEHComponent
{
    GENERATED_BODY()

#pragma region Base

public:
    void Init(USceneComponent* InTarget, UAudioComponent* InMoveAC, UTimelineComponent* InTimeline, const FElevatorMoveConfig& InConfig);
    
protected:
    virtual void BeginPlay() override;

#pragma endregion

#pragma region Move

public:
    void SetToStart();
    void SetToMap();
    void PlayArrival();
    void PlayDeparture();
    void CancelMove();
    void StopMoveSound();

    FVector GetStartLocation() const { return Config.StandardPos + Config.StartPos; }
    FVector GetMapLocation() const { return Config.StandardPos + Config.MapPos; }
    FVector GetEndLocation() const { return Config.StandardPos + Config.EndPos; }
    float GetMoveDuration() const { return MoveDuration; }
    bool IsMoving() const { return bIsMoving; }

    DECLARE_MULTICAST_DELEGATE(FOnElevatorMoveFinished);
    FOnElevatorMoveFinished OnMoveFinished;
    
protected:
    UPROPERTY(EditAnywhere, Category = "Movement|Elevator", meta = (ClampMin = "0.1"))
    float MoveDuration = 3.0f;

private:
    UFUNCTION()
    void HandleTimelineUpdate(float Alpha);

    UFUNCTION()
    void HandleTimelineFinished();

    void BeginMove(const FVector& From, const FVector& To);

    UPROPERTY()
    TObjectPtr<USceneComponent> MoveTarget;

    UPROPERTY()
    TObjectPtr<UAudioComponent> MoveAC;

    UPROPERTY()
    TObjectPtr<UTimelineComponent> MoveTimeline;
    
    FElevatorMoveConfig Config;
    FVector MoveFrom = FVector::ZeroVector;
    FVector MoveTo = FVector::ZeroVector;
    bool bIsMoving = false;

#pragma endregion
    
};