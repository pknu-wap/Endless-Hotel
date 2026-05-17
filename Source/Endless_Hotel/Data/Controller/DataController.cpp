// Copyright by 2025-2 WAP Game 2 team

#include "Data/Controller/DataController.h"
#include "Data/Anomaly/AnomalyData.h"
#include "Anomaly/Base/Anomaly_Event.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Asset/Manager/EHAssetManager.h"
#include "Type/Anomaly/Type_AnomalyType.h"
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

	TArray<uint8> AnomalyList;
	OriginAnomaly.Empty();

	if (!DataTable_Anomaly)
	{
		return;
	}

	for (auto RowData : DataTable_Anomaly->GetRowMap())
	{
		FAnomalyData* Data = (FAnomalyData*)RowData.Value;
		AnomalyList.Add(static_cast<uint8>(Data->AnomalyID));
	}

	if (AnomalyList.IsEmpty())
	{
		for (int index = 0; index < MaxIndex; ++index)
		{
			AnomalyList.Add(index);
		}
	}

	TArray<UPDA_Anomaly*> Datas = AssetManager.GetAnomalyDataAsset(AnomalyList);
	
	for (UPDA_Anomaly* PDA : Datas)
	{
		if (!PDA) 
		{
			continue;
		}

		FAnomalyEntry Entry;
		Entry.AnomalyID = PDA->ID;
		Entry.AnomalyClass = PDA->Anomaly;
		for (const TSoftClassPtr<AAnomaly_Object_Base>& SoftClassPtr : PDA->Objects)
		{
			if (UClass* LoadedClass = SoftClassPtr.LoadSynchronous())
			{
				Entry.ObjectClasses.Add(LoadedClass);
			}
		}

		OriginAnomaly.Add(Entry);
	}
}

TArray<TSubclassOf<AAnomaly_Object_Base>> UDataController::GetObjectByID(EAnomalyID AnomalyID)
{
	TArray<TSubclassOf<AAnomaly_Object_Base>> ResultArray;
	for (const FAnomalyEntry& Entry : OriginAnomaly)
	{
		if (Entry.AnomalyID == AnomalyID)
		{
			for (UClass* ObjClass : Entry.ObjectClasses)
			{
				ResultArray.Add(ObjClass);
			}
			break;
		}
	}
	return ResultArray;
}

void UDataController::RemoveClearedAnomaly()
{
	ActAnomaly.RemoveAll([this](const FAnomalyEntry& Entry)
		{
			return ClearedAnomalySet.Contains(Entry.AnomalyID);
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
	ActAnomaly.RemoveAll([GameSystem](const FAnomalyEntry& Entry)
		{
			const AAnomaly_Event* DefaultObj = GetDefault<AAnomaly_Event>(Entry.AnomalyClass.Get());
			return !GameSystem->AnomalyRules.Contains(DefaultObj->AnomalyRule);
		});
}

uint8 UDataController::GetRemainingAnomalyCounts()
{
	return OriginAnomaly.Num() - ClearedAnomalySet.Num();
}

#pragma endregion