// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Actor/EHActor.h"
#include "Type/Anomaly/Type_AnomalyID.h"
#include "Type/Level/Type_Level.h"
#include <CoreMinimal.h>
#include <Anomaly_Generator.generated.h>

#pragma region Declare

// Forward Declaration
class AAnomaly_Event;
class AAnomaly_Object_Base;

struct FAnomalySpawnInfo
{
	bool bIsNormal = false;
	uint8 Index = 0;
	EAnomalyID AnomalyID = EAnomalyID::None;
	EHotelDataLayer DataLayer = EHotelDataLayer::Hotel;
};

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Generator : public AEHActor
{
	GENERATED_BODY()

#pragma region Object

private:
	void SpawnAnomalyObject(uint8 AnomalyID, FTransform SpawnTransform, FActorSpawnParameters Params, const TSubclassOf<AAnomaly_Object_Base> TargetClass);
	void AnomalyObjectLinker(const TArray<TSubclassOf<AAnomaly_Object_Base>>& TargetClasses);

#pragma endregion

#pragma region Base

protected:
	virtual void BeginPlay();

#pragma endregion

#pragma region Generate & State

public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Anomaly|State")
	TObjectPtr<AAnomaly_Event> CurrentAnomaly;

	TOptional<FAnomalySpawnInfo> NextAnomalyData;

#pragma endregion

#pragma region SpawnAnomaly

public:
	UFUNCTION()
	void SpawnAnomaly();

	FAnomalySpawnInfo DecideAnomaly(uint8 Index);
	FAnomalySpawnInfo DecideNext();
	AAnomaly_Event* SpawnFromInfo(const FAnomalySpawnInfo& Info, ULevel* SpawnLevel);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Anomaly|Normal")
	TSoftClassPtr<AAnomaly_Event> NormalClass;

private:
	bool bIsInitialFloor = true;

#pragma endregion

};