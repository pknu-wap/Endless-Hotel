// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Actor/EHActor.h"
#include <CoreMinimal.h>
#include <Anomaly_Generator.generated.h>

#pragma region Declare

// Forward Declaration
class AAnomaly_Event;

// Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnomalySpawned, AAnomaly_Event*, Spawned);

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Generator : public AEHActor
{
	GENERATED_BODY()

#pragma region Linker

	void AnomalyObjectLinker();

#pragma endregion

#pragma region Generate & State

public:
	UPROPERTY(VisibleInstanceOnly)
	bool bDidInitialSpawn = false;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Anomaly|State")
	TObjectPtr<AAnomaly_Event> CurrentAnomaly;

#pragma endregion

#pragma region Event
	
	UPROPERTY(BlueprintAssignable, Category = "Anomaly|Event")
	FOnAnomalySpawned OnAnomalySpawned;

#pragma endregion

#pragma region Generate Anomaly

public:
	AAnomaly_Event* SpawnAnomalyAtIndex(uint8 Index, ULevel* SpawnLevel);

	AAnomaly_Event* SpawnNormal(ULevel* SpawnLevel);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Anomaly|Normal")
	TSoftClassPtr<AAnomaly_Event> NormalClass;

#pragma endregion

};