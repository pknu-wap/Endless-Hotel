// Copyright by 2026-1 WAP Game 2 team

#include "Asset/Manager/EHAssetManager.h"
#include "Asset/DataAsset/Anomaly/PDA_Anomaly.h"

#pragma region Anomaly

void UEHAssetManager::LoadAnomalyDataAsset()
{
	if (!AnomalyDatas.IsEmpty())
	{
		return;
	}

	TArray<FPrimaryAssetId> IDs;
	GetPrimaryAssetIdList(FPrimaryAssetType("Anomaly"), OUT IDs);

	for (const auto& ID : IDs)
	{
		LoadPrimaryAsset(ID)->WaitUntilComplete();
		AnomalyDatas.Add(GetPrimaryAssetObject<UPDA_Anomaly>(ID));
	}

	AnomalyDatas.Sort([](const UPDA_Anomaly& First, const UPDA_Anomaly& Second)
		{
			return First.Number < Second.Number;
		});
}

TArray<UPDA_Anomaly*> UEHAssetManager::GetAnomalyDataAsset(const TArray<uint8>& Indexes)
{
	TArray<UPDA_Anomaly*> ReturnArray;

	for (const uint8& Index : Indexes)
	{
		if (AnomalyDatas.IsValidIndex(Index))
		{
			ReturnArray.Add(AnomalyDatas[Index]);
		}
	}

	return ReturnArray;
}

#pragma endregion