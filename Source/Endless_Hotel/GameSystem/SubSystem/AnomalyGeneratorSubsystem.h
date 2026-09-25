// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/Anomaly/Type_AnomalyID.h"
#include "Type/Anomaly/Type_AnomalyRule.h"
#include "Type/Level/Type_Level.h"
#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <AnomalyGeneratorSubsystem.generated.h>

#pragma region Declare

// Forward Declaration
class AAnomaly_Event;
class AAnomaly_Object_Base;

struct FAnomalySpawnInfo
{
	bool bIsNormal = false;
	EAnomalyID AnomalyID = EAnomalyID::None;
	EMapDataLayer DataLayer = EMapDataLayer::Hotel;
	EAnomalyRule Rule = EAnomalyRule::None;
	UPROPERTY()
	TSoftClassPtr<AAnomaly_Event> EventClass;
};

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API UAnomalyGeneratorSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

#pragma region Object

private:
	void AnomalyObjectLinker(const TArray<TSubclassOf<AAnomaly_Object_Base>>& TargetClasses) const;

#pragma endregion

#pragma region Base

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

#pragma endregion

#pragma region Generate & State

public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Anomaly|State")
	TObjectPtr<AAnomaly_Event> CurrentAnomaly;

	TOptional<FAnomalySpawnInfo> NextAnomalyData;

#pragma endregion

#pragma region SpawnAnomaly

public:
	void SpawnAnomaly();

	TOptional<FAnomalySpawnInfo> DecideAnomaly(uint8 Index) const;
	TOptional<FAnomalySpawnInfo> DecideNext() const;
	AAnomaly_Event* SpawnFromInfo(const FAnomalySpawnInfo& Info) const;

private:
	bool bIsInitialFloor = true;

#pragma endregion

#pragma region Debug

public:
	bool SetNextAnomalyForced(EAnomalyID ID);

#pragma endregion

#pragma region Reset

public:
	void ResetGenerator();

#pragma endregion

};