// Copyright by 2026-1 WAP Game 2 team

#include "Asset/Manager/EHAssetManager.h"
#include "Asset/DataAsset/Anomaly/PDA_Anomaly.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"

#pragma region AnomalyData|Query

FAnomalyEntry UEHAssetManager::GetAnomalyData(uint8 Index)
{
	LoadAnomalyData();

	if (!IsValidIndexAnomalyData(Index))
	{
		return FAnomalyEntry();
	}

	return Data_Anomalies[Index];
}

TArray<FAnomalyEntry> UEHAssetManager::GetAnomalyData(TArray<uint8> Indexes)
{
	LoadAnomalyData();

	TArray<FAnomalyEntry> ReturnArray;

	for (uint8 Index : Indexes)
	{
		if (!IsValidIndexAnomalyData(Index))
		{
			continue;
		}

		ReturnArray.AddUnique(Data_Anomalies[Index]);
	}

	return ReturnArray;
}

TArray<FAnomalyEntry> UEHAssetManager::GetAnomalyData(TArray<EAnomalyID> IDs)
{
	LoadAnomalyData();

	TArray<FAnomalyEntry> ReturnArray;

	for (EAnomalyID ID : IDs)
	{
		int32 Index = 0;

		if (!Data_Anomalies.Find(ID, Index))
		{
			continue;
		}

		ReturnArray.AddUnique(Data_Anomalies[Index]);
	}

	return ReturnArray;
}

void UEHAssetManager::LoadAnomalyData()
{
	if (!Data_Anomalies.IsEmpty())
	{
		return;
	}

	TArray<FPrimaryAssetId> IDs;
	GetPrimaryAssetIdList(FPrimaryAssetType("Anomaly"), OUT IDs);

	for (const auto& ID : IDs)
	{
		LoadPrimaryAsset(ID)->WaitUntilComplete();

		auto* PDA_Anomaly = GetPrimaryAssetObject<UPDA_Anomaly>(ID);

		for (FAnomalyEntry Data : PDA_Anomaly->Entries)
		{
			Data_Anomalies.Add(Data);
		}
	}

	Data_Anomalies.Sort([](const FAnomalyEntry& First, const FAnomalyEntry& Second)
		{
			return static_cast<uint8>(First.ID) < static_cast<uint8>(Second.ID);
		});
}

#pragma endregion

#pragma region Entry|Setup

void UEHAssetManager::InitAnomalyEntries()
{
	LoadAnomalyData();

	OriginAnomaly.Empty();
	ActAnomaly.Empty();

	for (const FAnomalyEntry& Entry : Data_Anomalies)
	{
		if (Entry.ID == EAnomalyID::Normal)
		{
			NormalAnomalyData = Entry;
			continue;
		}

		OriginAnomaly.Add(Entry);
	}

	ActAnomaly = OriginAnomaly;
}

void UEHAssetManager::RebuildActAnomalyFromOrigin()
{
	ActAnomaly.Empty();
	ActAnomaly.Append(OriginAnomaly);
}

void UEHAssetManager::RemoveNoRuleAnomaly(const TArray<EAnomalyRule>& ActiveRules)
{
	ActAnomaly.RemoveAll([this, &ActiveRules](const FAnomalyEntry& Entry)
		{
			return !CanSpawnAnomaly(Entry, ActiveRules);
		});
}

void UEHAssetManager::ShuffleActAnomaly()
{
	if (ActAnomaly.Num() > 1)
	{
		for (uint8 CurrentIndex = ActAnomaly.Num() - 1; CurrentIndex > 0; --CurrentIndex)
		{
			const uint8 RandomIndex = FMath::RandRange(0, CurrentIndex);
			if (CurrentIndex != RandomIndex)
			{
				ActAnomaly.Swap(CurrentIndex, RandomIndex);
			}
		}
	}
}

#pragma endregion

#pragma region Anomaly|ClearState

void UEHAssetManager::ResetClearedAnomaly()
{
	ClearedAnomalySet.Empty();
}

void UEHAssetManager::RemoveClearedAnomaly()
{
	ActAnomaly.RemoveAll([this](const FAnomalyEntry& Entry)
		{
			return ClearedAnomalySet.Contains(Entry.ID);
		});
}

#pragma endregion

#pragma region Anomaly|Getter

uint8 UEHAssetManager::GetRemainingAnomalyCounts() const
{
	return OriginAnomaly.Num() - ClearedAnomalySet.Num();
}

TArray<TSubclassOf<AAnomaly_Object_Base>> UEHAssetManager::GetObjectByID(EAnomalyID AnomalyID)
{
	TArray<TSubclassOf<AAnomaly_Object_Base>> ResultArray;

	auto LoadObjects = [&ResultArray](const TArray<FAnomalyObjectRequirement>& Requirements)
		{
			for (const auto& Requirement : Requirements)
			{
				if (UClass* Loaded = Requirement.ObjectClass.LoadSynchronous())
				{
					ResultArray.AddUnique(Loaded);
				}
			}
		};

	if (AnomalyID == EAnomalyID::Normal)
	{
		LoadObjects(NormalAnomalyData.ObjectSettings);
		return ResultArray;
	}

	if (const auto* Entry = OriginAnomaly.FindByPredicate([AnomalyID](const auto& E) { return E.ID == AnomalyID; }))
	{
		LoadObjects(Entry->ObjectSettings);
	}

	return ResultArray;
}

TArray<FAnomalyObjectRequirement> UEHAssetManager::GetObjectRequirements(EAnomalyID AnomalyID)
{
	if (AnomalyID == EAnomalyID::Normal)
	{
		return NormalAnomalyData.ObjectSettings;
	}

	if (const auto* Entry = OriginAnomaly.FindByPredicate([AnomalyID](const auto& E) { return E.ID == AnomalyID; }))
	{
		return Entry->ObjectSettings;
	}

	return {};
}

bool UEHAssetManager::CanSpawnAnomaly(const FAnomalyEntry& AnomalyEntry, const TArray<EAnomalyRule>& ActiveRules) const
{
	return ActiveRules.Contains(AnomalyEntry.Rule);
}

#pragma endregion

#pragma region ForDebug

void UEHAssetManager::AddToSpawnList(EAnomalyID AnomalyID)
{
	if (ActAnomaly.ContainsByPredicate([AnomalyID](const FAnomalyEntry& E) { return E.ID == AnomalyID; }))
	{
		return;
	}

	if (const auto* Found = OriginAnomaly.FindByPredicate([AnomalyID](const FAnomalyEntry& E) { return E.ID == AnomalyID; }))
	{
		ActAnomaly.Add(*Found);
		UE_LOG(LogTemp, Log, TEXT("[Debug] Added Anomaly to spawn list: %s"), *UEnum::GetValueAsString(AnomalyID));
	}
}

void UEHAssetManager::RemoveFromSpawnList(EAnomalyID AnomalyID)
{
	const int32 Removed = ActAnomaly.RemoveAll([AnomalyID](const FAnomalyEntry& E) { return E.ID == AnomalyID; });
	UE_LOG(LogTemp, Log, TEXT("[Debug] Removed %d entries of Anomaly: %s"), Removed, *UEnum::GetValueAsString(AnomalyID));
}

bool UEHAssetManager::TryGetActAnomalyEntryByID(EAnomalyID AnomalyID, FAnomalyEntry& OutEntry) const
{
	if (const FAnomalyEntry* Found = ActAnomaly.FindByPredicate([AnomalyID](const FAnomalyEntry& E) { return E.ID == AnomalyID; }))
	{
		OutEntry = *Found;
		return true;
	}

	return false;
}

FString UEHAssetManager::GetActAnomalyListAsString() const
{
	if (ActAnomaly.IsEmpty())
	{
		return TEXT("(empty)");
	}

	FString Result;
	for (const FAnomalyEntry& Entry : ActAnomaly)
	{
		Result += UEnum::GetValueAsString(Entry.ID) + TEXT(",\n");
	}

	Result.RemoveFromEnd(TEXT(",\n"));
	return Result;
}

#pragma endregion