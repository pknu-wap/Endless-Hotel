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

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Linker

	void AnomalyObjectLinker();

#pragma endregion

#pragma region Generate & State

public:
	UPROPERTY(VisibleInstanceOnly)
	bool bDidInitialSpawn = false;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Anomaly|State")
	TWeakObjectPtr<AAnomaly_Base> CurrentAnomaly;

#pragma endregion

#pragma region Event
	
	UPROPERTY(BlueprintAssignable, Category = "Anomaly|Event")
	FOnAnomalySpawned OnAnomalySpawned;

#pragma endregion

#pragma region Generate Anomaly

public:
	UFUNCTION()
	AAnomaly_Base* SpawnAnomalyAtIndex(uint8 Index);

	UFUNCTION()
	AAnomaly_Base* SpawnNormal();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Anomaly|Normal")
	TSubclassOf<AAnomaly_Base> NormalClass;

#pragma endregion

#pragma region ForTest

public:
	UPROPERTY(EditAnywhere, Category = "Anomaly|Test")
	TArray<TSubclassOf<AAnomaly_Base>> OriginAnomaly;

protected:
	UFUNCTION()
	void AddAnomaly();

#pragma endregion
};