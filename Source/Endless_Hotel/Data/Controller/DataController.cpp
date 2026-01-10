// Copyright by 2025-2 WAP Game 2 team

#include "Data/Controller/DataController.h"
#include "Data/Compendium/Compendium.h"
#include "Anomaly/Base/Anomaly_Base.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Data/Anomaly/AnomalyData.h"

#pragma region Base

UDataController::UDataController()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> CompendiumFinder(TEXT("/Game/EndlessHotel/Data/DT_Compendium.DT_Compendium"));
	if (CompendiumFinder.Succeeded())
	{
		DataTable_Compendium = CompendiumFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> AnomalyFinder(TEXT("/Game/EndlessHotel/Data/DT_AnomalyData.DT_AnomalyData"));
	if (AnomalyFinder.Succeeded())
	{
		DataTable_Anomaly = AnomalyFinder.Object;
	}
}

#pragma endregion

#pragma region Compendium

FCompendium* UDataController::GetCompendiumData(int32 Index)
{
	return DataTable_Compendium->FindRow<FCompendium>(*FString::FromInt(Index), TEXT(""));
}

FCompendium* UDataController::GetCompendiumData(FString Name)
{
	FCompendium* Data = nullptr;

	for (auto RowData : DataTable_Compendium->GetRowMap())
	{
		Data = (FCompendium*)RowData.Value;

		if (Data->Name == Name)
		{
			return Data;
		}
	}

	return nullptr;
}

FCompendium* UDataController::GetCompendiumData(int32 Page, int32 Number)
{
	FCompendium* Data = nullptr;

	for (auto RowData : DataTable_Compendium->GetRowMap())
	{
		Data = (FCompendium*)RowData.Value;

		if (Data->Page == Page && Data->Number == Number)
		{
			return Data;
		}
	}

	return nullptr;
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
		
		UClass* LoadedClass = StaticLoadClass(AAnomaly_Base::StaticClass(), nullptr, *Data->AnomalyPath);
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

TSubclassOf<AAnomaly_Object_Base> UDataController::GetObjectByName(FString ObjectName)
{
	for (auto& Pair : DataTable_Anomaly->GetRowMap())
	{
		const FAnomalyData* Row = reinterpret_cast<const FAnomalyData*>(Pair.Value);
		if (Row->Anomaly_En == ObjectName)
		{
			UClass* LoadedClass = StaticLoadClass(AAnomaly_Object_Base::StaticClass(), nullptr, *Row->ObjectPath);
			return LoadedClass;
		}
	}
	return nullptr;
}

TSubclassOf<AAnomaly_Object_Base> UDataController::GetObjectByRowIndex(uint8 RowIndex)
{
	if (const FAnomalyData* Data = DataTable_Anomaly->FindRow<FAnomalyData>(*FString::FromInt(RowIndex), TEXT("")))
	{
		UClass* LoadedClass = StaticLoadClass(AAnomaly_Object_Base::StaticClass(), nullptr, *Data->ObjectPath);
		return LoadedClass;
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