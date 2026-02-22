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
	uint8 AnomalyID = 0;

	UPROPERTY()
	TSoftClassPtr<class AAnomaly_Event> AnomalyClass;

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

#pragma region AnomalyDataBase

public:
	void GetAnomalyEntries();

	TSubclassOf<class AAnomaly_Object_Base> GetObjectByID(uint8 ObjectID);

	TArray<FAnomalyEntry> GetOriginAnomaly() { return OriginAnomaly; }

	void RemoveClearedAnomaly();

public:
	UPROPERTY()
	TSet<uint8> LoadedAnomalySet;

	UPROPERTY()
	TArray<FAnomalyEntry> ActAnomaly;

protected:
	UPROPERTY()
	TObjectPtr<class UDataTable> DataTable_Anomaly;

private:
	UPROPERTY()
	TArray<FAnomalyEntry> OriginAnomaly;

#pragma endregion

};