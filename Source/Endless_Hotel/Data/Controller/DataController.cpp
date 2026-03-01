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
		if (Data->AnomalyPath.IsEmpty()) continue;
		
		UClass* LoadedClass = StaticLoadClass(AAnomaly_Event::StaticClass(), nullptr, *Data->AnomalyPath);

		TArray<FString> PathStrings;
		Data->ObjectPath.ParseIntoArray(PathStrings, TEXT(";"), true);

		TArray<UClass*> LoadedObjectClasses;
		for (const FString& SinglePath : PathStrings)
		{
			FString TrimmedPath = SinglePath.TrimStartAndEnd();
			if (TrimmedPath.IsEmpty()) continue;

			UClass* ObjClass = StaticLoadClass(AAnomaly_Object_Base::StaticClass(), nullptr, *TrimmedPath);
			if (ObjClass)
			{
				LoadedObjectClasses.Add(ObjClass);
			}
		}

		if (LoadedClass)
		{
			OriginAnomaly.Add(FAnomalyEntry{ Data->AnomalyID, LoadedClass, LoadedObjectClasses });
		}
	}
}

TArray<TSubclassOf<AAnomaly_Object_Base>> UDataController::GetObjectByID(uint8 AnomalyID)
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
			return LoadedAnomalySet.Contains(Entry.AnomalyID);
		});
}

#pragma endregion