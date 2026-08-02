// Copyright by 2026-1 WAP Game 2 team

#include "Asset/Manager/EHAssetManager.h"
#include "Asset/DataAsset/Anomaly/PDA_Anomaly.h"

#pragma region Anomaly

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