// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Type_Interact.generated.h>

UENUM(BlueprintType)
enum class EInteractType : uint8
{
	None		UMETA(DisplayName = "None"),
	Restore		UMETA(DisplayName = "Restore"),
	Rotate		UMETA(DisplayName = "Rotate"),
	TurnOff		UMETA(DisplayName = "TurnOff"),
	Burn		UMETA(DisplayName = "Burn"),
	Elevator	UMETA(DisplayName = "Elevator")
};

USTRUCT(BlueprintType)
struct FInteractInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere)
	EInteractType InteractType = EInteractType::None;

	UPROPERTY()
	bool bIsInteracted = false;

	UPROPERTY(EditAnyWhere)
	FText Description;
};