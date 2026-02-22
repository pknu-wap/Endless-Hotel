// Copyright by 2025-2 WAP Game 2 team

#include "Data/Controller/DataController.h"
#include "Data/Anomaly/AnomalyData.h"
#include "Anomaly/Base/Anomaly_Event.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"

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
	if (!DataTable_Anomaly) return;

	for (auto RowData : DataTable_Anomaly->GetRowMap())
	{
		FAnomalyData* Data = (FAnomalyData*)RowData.Value;
		if (Data->AnomalyPath.IsEmpty()) return;
		
		UClass* LoadedClass = StaticLoadClass(AAnomaly_Event::StaticClass(), nullptr, *Data->AnomalyPath);
		UClass* ObjectClass = StaticLoadClass(AAnomaly_Object_Base::StaticClass(), nullptr, *Data->ObjectPath);

		if (LoadedClass)
		{
			OriginAnomaly.Add(FAnomalyEntry{ Data->AnomalyID, LoadedClass, ObjectClass });
		}
	}
}

TSubclassOf<AAnomaly_Object_Base> UDataController::GetObjectByID(uint8 AnomalyID)
{
	for (auto& Pair : DataTable_Anomaly->GetRowMap())
	{
		const FAnomalyData* Row = reinterpret_cast<const FAnomalyData*>(Pair.Value);
		if (Row->AnomalyID == AnomalyID)
		{
			UClass* LoadedClass = StaticLoadClass(AAnomaly_Object_Base::StaticClass(), nullptr, *Row->ObjectPath);
			return LoadedClass;
		}
	}
	return nullptr;
}

void UDataController::RemoveClearedAnomaly()
{
	ActAnomaly.RemoveAll([this](const FAnomalyEntry& Entry)
		{
			return LoadedAnomalySet.Contains(Entry.AnomalyID);
		});
}

#pragma endregion