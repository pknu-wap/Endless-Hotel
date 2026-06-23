// Copyright by 2026-1 WAP Game 2 team

#include "Asset/Manager/EHAssetManager.h"
#include "Asset/DataAsset/Anomaly/PDA_Anomaly.h"

#pragma region Anomaly

TArray<UPDA_Anomaly*> UEHAssetManager::GetAnomalyDataAsset(const TArray<uint8>& Indexes)
{
	LoadAnomalyDataAsset();

	TArray<UPDA_Anomaly*> ReturnArray;

	for (const uint8& Index : Indexes)
	{
		auto FoundPDA = DA_Anomalies.FindByPredicate([Index](const TObjectPtr<UPDA_Anomaly>& Item)
			{
				return Item->Entries.ContainsByPredicate([Index](const FAnomalyEntry& Entry)
					{
						return static_cast<uint8>(Entry.ID) == Index;
					});
			});

        if (FoundPDA && *FoundPDA)
        {
            ReturnArray.Add(*FoundPDA);
        }
	}

	return ReturnArray;
}

void UEHAssetManager::LoadAnomalyDataAsset()
{
	if (!DA_Anomalies.IsEmpty())
	{
		return;
	}

	TArray<FPrimaryAssetId> IDs;
	GetPrimaryAssetIdList(FPrimaryAssetType("Anomaly"), OUT IDs);

	for (const auto& ID : IDs)
	{
		LoadPrimaryAsset(ID)->WaitUntilComplete();
		DA_Anomalies.Add(GetPrimaryAssetObject<UPDA_Anomaly>(ID));
	}

	DA_Anomalies.RemoveAll([](const TObjectPtr<UPDA_Anomaly>& PDA)
		{
			return !PDA || PDA->Entries.IsEmpty();
		});

	for (auto& PDA : DA_Anomalies)
	{
		if (!PDA) continue;
		PDA->Entries.Sort([](const FAnomalyEntry& A, const FAnomalyEntry& B)
			{
				return A.ID < B.ID;
			});
	}

	DA_Anomalies.Sort([](const TObjectPtr<UPDA_Anomaly> First, const TObjectPtr<UPDA_Anomaly> Second)
		{
			return First->Entries[0].ID < Second->Entries[0].ID;
		});
}

#pragma endregion