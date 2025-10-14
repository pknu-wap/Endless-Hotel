// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Anomaly_Generator.generated.h"

#pragma region Declare

// Forward Declaration
<<<<<<< HEAD
class AAnomaly_Base_Ex;

// Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnomalySpawned, AAnomaly_Base_Ex*, Spawned);
=======
class AAnomaly_Base;

// Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnomalySpawned, AAnomaly_Base*, Spawned);
>>>>>>> parent of ced9334 (Revert "Merge remote-tracking branch 'origin/Develop' into origin/Feature/Anomaly")

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Generator : public AActor
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Generator(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

#pragma endregion

#pragma region Generate & State

	// Original Pool
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anomaly")
	TArray<TSubclassOf<AAnomaly_Base>> Origin_Anomaly;

	// Active Pool
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Anomaly")
	TArray<TSubclassOf<AAnomaly_Base>> Act_Anomaly;

	// Current Index
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Anomaly|State")
	int32 Current_AnomalyID = -1;

	// SpawnPoints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Spawn")
	TArray<FTransform> SpawnPoints;

	// SpawnPoint Index
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Spawn")
	int32 SpawnIndex = 0;

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

#pragma region Pool & Sequence

public:

	// Initialize Pool
	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	void InitializePool(bool bShuffle = true);

	// Reset Sequence (re-shuffle if true)
	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	void ResetSequence(bool bShuffle = true);

#pragma endregion

#pragma region Generate Anomaly
public:
	// Spawn Next Anomaly in Sequence
	UFUNCTION(BlueprintCallable, Category = "Anomaly")
<<<<<<< HEAD
	AAnomaly_Base_Ex* SpawnNextAnomaly(bool bDestroyPrev = true);
=======
	AAnomaly_Base* SpawnNextAnomaly(bool bDestroyPrev = true);
>>>>>>> parent of ced9334 (Revert "Merge remote-tracking branch 'origin/Develop' into origin/Feature/Anomaly")

	// Spawn Anomaly at Specific Index
	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	AAnomaly_Base* SpawnAnomalyAtIndex(int32 Index, bool bDestroyPrev = true);

	// Destroy Current Anomaly
	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	bool DestroyCurrentAnomaly();

#pragma endregion

protected:
	virtual void BeginPlay() override;
	
#pragma region Internals

private:
	// Pick Random Spawn Transform
	FTransform PickSpawnTransform() const;

#pragma endregion
};
