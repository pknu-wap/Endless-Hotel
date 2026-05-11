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

protected:
	UPROPERTY(EditAnyWhere, Category = "Data|Map")
	TObjectPtr<class UPDA_Map> DA_Map;

private:
	TMap<FName, TSharedPtr<struct FStreamableHandle>> DA_Map_Handles;

#pragma endregion

#pragma region Level

public:
	void LoadLevel(const ELevelType& LevelType);
	void OpenLevel();

	void LoadDataLayer(const EHotelDataLayer& Layer);
	void SwitchDataLayer();

public:
	ELevelType CurrentLevelType = ELevelType::Persistent;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelLoaded);
	FOnLevelLoaded OnLevelLoaded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelOpened, ELevelType);
	FOnLevelOpened OnLevelOpened;

#pragma endregion

#pragma region Player

protected:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	FTransform DefaultTransform = FTransform(FRotator(0, 180, 0), FVector(-1200, 1100, 680), FVector(0.75f, 0.75f, 0.75f));

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere, Category = "Widget|HUD")
	TSubclassOf<class UUI_Base> UI_HUD_InGame_Class;

	UPROPERTY(EditAnywhere, Category = "Widget|HUD")
	TSubclassOf<class UUI_Base> UI_HUD_Title_Class;

	UPROPERTY(EditAnywhere, Category = "Widget|PopUp")
	TSubclassOf<class UUI_Base> UI_Loading_Class;

#pragma endregion

};