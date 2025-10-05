// Copyright by 2025-2 WAP Game 2 team

#include "Data/Controller/DataController.h"
#include "Data/Compendium/Compendium.h"

#pragma region Base

UDataController::UDataController()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> CompendiumFinder(TEXT("/Game/EndlessHotel/Data/DT_Compendium.DT_Compendium"));
	if (CompendiumFinder.Succeeded())
	{
		DataTable_Compendium = CompendiumFinder.Object;
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