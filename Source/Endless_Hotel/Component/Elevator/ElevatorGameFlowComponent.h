// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Component/EHComponent.h"
#include <CoreMinimal.h>
#include <ElevatorGameFlowComponent.generated.h>

#pragma region Declare

enum class EMapDataLayer : uint8;

#pragma endregion

UCLASS(ClassGroup = (Elevator), meta = (BlueprintSpawnableComponent))
class ENDLESS_HOTEL_API UElevatorGameFlowComponent : public UEHComponent
{
	GENERATED_BODY()

#pragma region Verdict

public:
	void RequestVerdict() const;

protected:
	UPROPERTY(EditAnywhere, Category = "Verdict")
	bool bIsNormalElevator = true;

#pragma endregion

#pragma region Floor

public:
	void ScriptFloor() const;
	bool IsTopFloor() const;

#pragma endregion

#pragma region DataLayer

public:
	void RequestSwapDataLayer(EMapDataLayer InLayer) const;

#pragma endregion

#pragma region Progression

public:
	bool IsCheckIn() const;

#pragma endregion
	
#pragma region Target

public:
	void SetTargetElevator(FName InElevatorID) const;

#pragma endregion
	
};