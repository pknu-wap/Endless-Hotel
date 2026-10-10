// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Component/EHComponent.h"
#include <CoreMinimal.h>
#include <ElevatorDoorComponent.generated.h>

#pragma region Declare

class UBoxComponent;
class UTimelineComponent;

struct FElevatorDoorConfig
{
	UCurveFloat* Curve = nullptr;
	FVector LeftClosed = FVector::ZeroVector;
	FVector RightClosed = FVector::ZeroVector;
	FVector LeftOpen = FVector::ZeroVector;
	FVector RightOpen = FVector::ZeroVector;
	FVector BlockBoxActiveExtent = FVector::ZeroVector;
};

#pragma endregion

UCLASS(ClassGroup = (Elevator), meta = (BlueprintSpawnableComponent))
class ENDLESS_HOTEL_API UElevatorDoorComponent : public UEHComponent
{
	GENERATED_BODY()
	
#pragma region Base

public:
	void Init(UStaticMeshComponent* InLeftDoor, UStaticMeshComponent* InRightDoor, UAudioComponent* InDoorAC, UBoxComponent* InBlockBox, UTimelineComponent* InTimeline, const FElevatorDoorConfig& InConfig);
	
protected:
	virtual void BeginPlay() override;

#pragma endregion
	
#pragma region Move
	
public:
	void MoveDoors(bool bWillOpen);
	void ResetDoor();
	void SetDoorLighting(bool bVisibleFromOutside) const;

	bool IsOpened() const { return bIsOpened; }
	bool IsMoving() const { return bIsMoving; }
	
private:
	UFUNCTION()
	void HandleTimelineUpdate(float Alpha);
	
	UFUNCTION()
	void HandleTimelineFinished();
	
	void SetActiveBlockBox(bool bShouldBlock) const;
	
public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnElevatorDoorFinished, bool);
	FOnElevatorDoorFinished OnDoorFinished;
	
private:
	UPROPERTY()
	TObjectPtr<UTimelineComponent> DoorTimeline;
	
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> LeftDoor;
	
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> RightDoor;
	
	UPROPERTY()
	TObjectPtr<UAudioComponent> DoorAC;
	
	UPROPERTY()
	TObjectPtr<class UBoxComponent> BlockBox;
	
	UPROPERTY()
	TObjectPtr<UCurveFloat> DoorCurve;
	
	FVector LeftClosed, RightClosed, LeftOpen, RightOpen, BlockBoxActiveExtent;
	
	bool bIsOpened = false;
	bool bIsMoving = false;
	
#pragma endregion
	
};