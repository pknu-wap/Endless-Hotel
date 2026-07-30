// Copyright by 2025-2 WAP Game 2 team

#include "Data/Controller/DataController.h"
#include "Data/Anomaly/AnomalyData.h"
#include "Anomaly/Event/Anomaly_Event.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Asset/Manager/EHAssetManager.h"
#include "Asset/DataAsset/Anomaly/PDA_Anomaly.h"
#include <GameSystem/SubSystem/GameSystem.h>

#pragma region Base

UDataController::UDataController()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> AnomalyFinder(TEXT("/Game/EndlessHotel/Data/DT_AnomalyData.DT_AnomalyData"));
	if (AnomalyFinder.Succeeded())
	{
		DataTable_Anomaly = AnomalyFinder.Object;
	}
}

#pragma endregion

#pragma region AnomalyDataBase

void UDataController::GetAnomalyEntries()
{
	auto& AssetManager = UEHAssetManager::Get();

	TArray<EAnomalyID> AnomalyList;
	OriginAnomaly.Empty();

	if (!DataTable_Anomaly)
	{
		return;
	}

	for (auto RowData : DataTable_Anomaly->GetRowMap())
	{
		FAnomalyData* Data = (FAnomalyData*)RowData.Value;
		AnomalyList.Add(Data->AnomalyID);
	}

	if (AnomalyList.IsEmpty())
	{
		const UEnum* Enum = StaticEnum<EAnomalyID>();
		
		for (int32 Index = 0; Index < Enum->NumEnums(); ++Index)
		{
			int64 Value = Enum->GetValueByIndex(Index);

			AnomalyList.Add(static_cast<EAnomalyID>(Value));
		}
	}
	else
	{
		AnomalyList.Add(EAnomalyID::Normal);
	}

	TArray<FAnomalyEntry> Datas = AssetManager.GetAnomalyData(AnomalyList);
	
	for (FAnomalyEntry Entry : Datas)
	{
		if (Entry.ID == EAnomalyID::Normal)
		{
			NormalAnomalyData = Entry;
			continue;
		}

		OriginAnomaly.Add(Entry);
	}
}

TArray<TSubclassOf<AAnomaly_Object_Base>> UDataController::GetObjectByID(EAnomalyID AnomalyID)
{
	TArray<TSubclassOf<AAnomaly_Object_Base>> ResultArray;

	auto LoadObjects = [&ResultArray](const TArray<TSoftClassPtr<AAnomaly_Object_Base>>& SoftClasses)
		{
			for (const auto& SoftClass : SoftClasses)
			{
				if (UClass* Loaded = SoftClass.LoadSynchronous())
				{
					ResultArray.Add(Loaded);
				}
			}
		};

	if (AnomalyID == EAnomalyID::Normal)
	{
		LoadObjects(NormalAnomalyData.Objects);
		return ResultArray;
	}

	if (const auto* Entry = OriginAnomaly.FindByPredicate([AnomalyID](const auto& E) { return E.ID == AnomalyID; }))
	{
		LoadObjects(Entry->Objects);
	}

	return ResultArray;
}

bool UDataController::CanSpawnAnomaly(const FAnomalyEntry& AnomalyEntry, const TArray<EAnomalyRule>& ActiveRules) const
{
	return ActiveRules.Contains(AnomalyEntry.Rule);
}

void UDataController::RemoveClearedAnomaly()
{
	ActAnomaly.RemoveAll([this](const auto& Entry)
		{
			return ClearedAnomalySet.Contains(Entry.ID);
		});
}

void UDataController::ResetClearedAnomaly()
{
	ClearedAnomalySet.Empty();
}

void UDataController::RemoveNoRuleAnomaly()
{
	// Temp Logic : Remove Anomaly By Rule
	auto* GameSystem = GetGameInstance()->GetSubsystem<UGameSystem>();
	ActAnomaly.RemoveAll([this, GameSystem](const FAnomalyEntry& Entry)
		{
			return !CanSpawnAnomaly(Entry, GameSystem->AnomalyRules);
		});
}

uint8 UDataController::GetRemainingAnomalyCounts()
{
	return OriginAnomaly.Num() - ClearedAnomalySet.Num();
}

#pragma endregion