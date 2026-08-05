// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Type/Anomaly/Type_AnomalyEntry.h"
#include "Type/Anomaly/Type_AnomalyID.h"
#include "Type/Anomaly/Type_AnomalyRule.h"
#include <CoreMinimal.h>
#include <Engine/AssetManager.h>
#include <EHAssetManager.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UEHAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
#pragma region Base

public:
	static UEHAssetManager& Get() { return *Cast<UEHAssetManager>(GEngine->AssetManager); }

#pragma endregion

#pragma region AnomalyData|Query

public:
	FAnomalyEntry GetAnomalyData(uint8 Index);
	TArray<FAnomalyEntry> GetAnomalyData(TArray<uint8> Indexes);
	TArray<FAnomalyEntry> GetAnomalyData(TArray<EAnomalyID> IDs);

	bool IsValidIndexAnomalyData(uint8 Index) { return Data_Anomalies.IsValidIndex(Index); }

private:
	void LoadAnomalyData();

#pragma endregion

#pragma region Entry|Setup

public:
	void InitAnomalyEntries();
	void RebuildActAnomalyFromOrigin();
	void RemoveNoRuleAnomaly(const TArray<EAnomalyRule>& ActiveRules);
	void ShuffleActAnomaly();

#pragma endregion

#pragma region Anomaly|ClearState

public:
	void ResetClearedAnomaly();
	void RemoveClearedAnomaly();
	void MarkAnomalyCleared(EAnomalyID ID) { ClearedAnomalySet.Add(ID); }

	int32 GetClearedAnomalyCount() const { return ClearedAnomalySet.Num(); }
	bool IsClearedAnomalySetEmpty() const { return ClearedAnomalySet.IsEmpty(); }
	TArray<EAnomalyID> GetClearedAnomalySet() const { return ClearedAnomalySet.Array(); }

#pragma endregion

#pragma region Anomaly|Getter

public:
	uint8 GetRemainingAnomalyCounts() const;
	TArray<TSubclassOf<AAnomaly_Object_Base>> GetObjectByID(EAnomalyID AnomalyID);
	TArray<FAnomalyObjectRequirement> GetObjectRequirements(EAnomalyID AnomalyID);
	const FAnomalyEntry& GetNormalAnomalyData() const { return NormalAnomalyData; }
	const FAnomalyEntry& GetActAnomalyByIndex(uint8 Index) const { return ActAnomaly.IsValidIndex(Index) ? ActAnomaly[Index] : NormalAnomalyData; }
	const TArray<FAnomalyEntry>& GetOriginAnomaly() const { return OriginAnomaly; }
	bool IsValidActAnomalyIndex(uint8 Index) const { return ActAnomaly.IsValidIndex(Index); }
	bool CanSpawnAnomaly(const FAnomalyEntry& AnomalyEntry, const TArray<EAnomalyRule>& ActiveRules) const;

#pragma endregion

#pragma region Anomaly|Data

private:
	UPROPERTY(Transient)
	TArray<FAnomalyEntry> Data_Anomalies;

	UPROPERTY(Transient)
	TArray<FAnomalyEntry> OriginAnomaly;

	UPROPERTY(Transient)
	TArray<FAnomalyEntry> ActAnomaly;

	UPROPERTY(Transient)
	FAnomalyEntry NormalAnomalyData;

	TSet<EAnomalyID> ClearedAnomalySet;

#pragma endregion

#pragma region ForDebug

public:
	FString GetActAnomalyListAsString() const;
	void AddToSpawnList(EAnomalyID AnomalyID);
	void RemoveFromSpawnList(EAnomalyID AnomalyID);
	bool TryGetActAnomalyEntryByID(EAnomalyID AnomalyID, FAnomalyEntry& OutEntry) const;

#pragma endregion

};