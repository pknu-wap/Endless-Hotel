// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/Level/Type_Level.h"
#include <CoreMinimal.h>
#include <Delegates/DelegateCombinations.h>
#include <Engine/GameInstance.h>
#include <EHGameInstance.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UEHGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
#pragma region Game

public:
	void QuitGame();

#pragma endregion

#pragma region Data

private:
	void LoadMapDataAsset(const FName& BundleName);

	UFUNCTION()
	void OnLoadedLevelDataAsset(FPrimaryAssetId DataAssetID);

protected:
	UPROPERTY(EditAnywhere, Category = "DataAsset")
	TObjectPtr<class UPDA_Level> PDA_Map;

#pragma endregion

#pragma region Level

public:
	void LoadLevel(const ELevelType& LevelType);
	void OpenLevel();

	void LoadDataLayer(const EHotelDataLayer& Layer);
	void SwitchDataLayer();

public:
	ELevelType CurrentLevelType = ELevelType::MainMenu;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelLoaded);
	FOnLevelLoaded OnLevelLoaded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelOpened, const ELevelType&, LevelType);
	FOnLevelOpened OnLevelOpened;

#pragma endregion

};