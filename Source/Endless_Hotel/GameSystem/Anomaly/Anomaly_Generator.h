// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Anomaly_Generator.generated.h"

#pragma region Declare

// Forward Declaration
class AAnomaly_Base;

// Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnomalySpawned, AAnomaly_Base*, Spawned);

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Generator : public AActor
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Generator(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

#pragma endregion

#pragma region Linker

	void AnomalyObjectLinker();

#pragma endregion

#pragma region Generate & State

public:
	// Initial Spawn Done
	UPROPERTY(VisibleInstanceOnly)
	bool bDidInitialSpawn = false;

	/** Living Anomaly */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Anomaly|State")
	TWeakObjectPtr<AAnomaly_Base> CurrentAnomaly;

#pragma endregion

#pragma region Event
	
	// Event when Anomaly is Spawned
	UPROPERTY(BlueprintAssignable, Category = "Anomaly|Event")
	FOnAnomalySpawned OnAnomalySpawned;

#pragma endregion

#pragma region Generate Anomaly
public:

	// Spawn Anomaly at Specific Index
	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	AAnomaly_Base* SpawnAnomalyAtIndex(int32 Index, bool bDestroyPrev = true);

	// Spawn Normal State
	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	AAnomaly_Base* SpawnNormal(bool bDestroyPrev = true);

	// Destroy Current Anomaly
	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	bool DestroyCurrentAnomaly();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Anomaly|Normal")
	TSubclassOf<AAnomaly_Base> NormalClass;

#pragma endregion

protected:
	virtual void BeginPlay() override;
};
