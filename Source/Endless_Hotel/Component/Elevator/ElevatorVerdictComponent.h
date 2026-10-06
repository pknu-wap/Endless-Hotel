// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Component/EHComponent.h"
#include <CoreMinimal.h>
#include <ElevatorVerdictComponent.generated.h>

UCLASS(ClassGroup = (Elevator), meta = (BlueprintSpawnableComponent))
class ENDLESS_HOTEL_API UElevatorVerdictComponent : public UEHComponent
{
	GENERATED_BODY()

#pragma region Verdict

public:
	void RequestVerdict() const;

protected:
	UPROPERTY(EditAnywhere, Category = "Verdict")
	bool bIsNormalElevator = true;

#pragma endregion
};