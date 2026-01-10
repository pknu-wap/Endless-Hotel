// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <DataController.generated.h>

#pragma region Declare

USTRUCT(BlueprintType)
struct FAnomalyEntry
{
	GENERATED_BODY()

	UPROPERTY()
	uint8 AnomalyID;

	UPROPERTY()
	TSubclassOf<class AAnomaly_Base> AnomalyClass;

	UPROPERTY()
	TSubclassOf<class AAnomaly_Object_Base> ObjectClass;
};

#pragma endregion

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

#pragma region AnomalyDataBase

public:
	void GetAnomalyEntries();

	TSubclassOf<class AAnomaly_Object_Base> GetObjectByID(uint8 ObjectID);

	TArray<FAnomalyEntry> GetOriginAnomaly() { return OriginAnomaly; }

	void RemoveClearedAnomaly();

public:
	TSet<uint8> LoadedAnomalySet;

	TArray<FAnomalyEntry> ActAnomaly;

protected:
	UPROPERTY()
	TObjectPtr<class UDataTable> DataTable_Anomaly;

private:
	TArray<FAnomalyEntry> OriginAnomaly;

#pragma endregion
};