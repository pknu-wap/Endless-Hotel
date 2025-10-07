// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataController.generated.h"

UCLASS()
class ENDLESS_HOTEL_API UDataController : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
#pragma region Base

public:
	UDataController();

#pragma endregion

#pragma region Compendium

public:
	struct FCompendium* GetCompendiumData(int32 Index);
	struct FCompendium* GetCompendiumData(FString Name);
	struct FCompendium* GetCompendiumData(int32 Page, int32 Number);

protected:
	UPROPERTY()
	TObjectPtr<class UDataTable> DataTable_Compendium;

#pragma endregion

};