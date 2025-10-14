// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExAnomaly/Anomaly_Base_Ex.h"
#include "Anomaly_Generator.generated.h"

#pragma region Declare

// Forward Declaration
class AAnomaly_Base;

// Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnomalySpawned, AAnomaly_Base*, Spawned);

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Generator : public AActor
{
	GENERATED_BODY()

public:
	AAnomaly_Generator(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Original Pool
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anomaly")
	TArray<TSubclassOf<AAnomaly_Base>> Origin_Anomaly;

	// Active Pool
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Anomaly")
	TArray<TSubclassOf<AAnomaly_Base>> Act_Anomaly;

	// Seed
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Anomaly|Random")
	int32 Seed = 12345;

	// Current Index
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Anomaly|State")
	int32 Current_AnomalyID = -1;

	// SPawnPoints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Spawn")
	TArray<FTransform> SpawnPoints;

	// SpawnPoint Index
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Spawn")
	int32 SpawnIndex = 0;

	// Event when Anomaly is Spawned
	UPROPERTY(BlueprintAssignable, Category = "Anomaly|Event")
	FOnAnomalySpawned OnAnomalySpawned;

	// Initial Spawn Done
	UPROPERTY(VisibleInstanceOnly)
	bool bDidInitialSpawn = false;

	/** Living Anomaly */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Anomaly|State")
	TWeakObjectPtr<AAnomaly_Base> CurrentAnomaly;

public:
	// ===== API =====
	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	void InitializePool(bool bShuffle = true);

	// Spawn Next Anomaly in Sequence
	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	AAnomaly_Base_Ex* SpawnNextAnomaly(bool bDestroyPrev = true);

	// Reset Sequence (re-shuffle if true)
	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	void ResetSequence(bool bShuffle = true);

#pragma endregion

#pragma region Generate Anomaly
public:
	// Spawn Next Anomaly in Sequence
	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	AAnomaly_Base* SpawnNextAnomaly(bool bDestroyPrev = true);

	// Spawn Anomaly at Specific Index
	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	AAnomaly_Base* SpawnAnomalyAtIndex(int32 Index, bool bDestroyPrev = true);

	// Destroy Current Anomaly
	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	bool DestroyCurrentAnomaly();

protected:
	virtual void BeginPlay() override;

private:
	// Random Stream
	mutable FRandomStream RS;

	// Pick Random Spawn Transform
	FTransform PickSpawnTransform() const;

	// Make Time Seed
	static int32 MakeTimeSeed();
};
