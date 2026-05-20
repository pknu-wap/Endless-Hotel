// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/Anomaly/Type_AnomalyType.h"
#include "Type/Anomaly/Type_AnomalyID.h"
#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <DataController.generated.h>


UCLASS()
class ENDLESS_HOTEL_API UDataController : public UGameInstanceSubsystem
{
	GENERATED_BODY()

#pragma region Base

public:
	UDataController();

#pragma endregion

#pragma region AnomalyDataBase

public:
	void GetAnomalyEntries();
	void RemoveClearedAnomaly();
	void ResetClearedAnomaly();
	void RemoveNoRuleAnomaly();
	uint8 GetRemainingAnomalyCounts();
	TArray<TSubclassOf<class AAnomaly_Object_Base>> GetObjectByID(EAnomalyID AnomalyID);
	TArray<FAnomalyEntry> GetOriginAnomaly() { return OriginAnomaly; }

public:
	UPROPERTY()
	TSet<EAnomalyID> ClearedAnomalySet;

	UPROPERTY()
	TArray<FAnomalyEntry> ActAnomaly;

	const uint8 MaxIndex = 255;

protected:
	UPROPERTY()
	TObjectPtr<class UDataTable> DataTable_Anomaly;

private:
	UPROPERTY()
	TArray<FAnomalyEntry> OriginAnomaly;

#pragma endregion

};