// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/Level/Type_Level.h"
#include <CoreMinimal.h>
#include <Engine/GameInstance.h>
#include <Delegates/DelegateCombinations.h>
#include <EHGameInstance.generated.h>

#pragma region Declare

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelLoaded);

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API UEHGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
#pragma region Level

public:
	void OpenLevel(const ELevelType& LevelName, bool bIsFirst = false);
	void QuitGame();

public:
	static ELevelType CurrentLevelType;

protected:
	UPROPERTY()
	TObjectPtr<class ULevelStreamingDynamic> CurrentLevel;

	UPROPERTY(EditAnyWhere, Category = "Level")
	TObjectPtr<UWorld> Level_MainMenu;

	UPROPERTY(EditAnyWhere, Category = "Level")
	TObjectPtr<UWorld> Level_Hotel;

#pragma endregion

#pragma region Loading

public:
	bool IsLevelLoaded();

protected:
	UFUNCTION()
	void LoadLevelCompleted();

	UFUNCTION()
	void ShowLevelCompleted();

	void UnloadCurrentLevel();

public:
	static FLevelLoaded OnLevelLoaded;

protected:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UUI_Base> UI_Loading;

#pragma endregion

#pragma region Anomaly

protected:
	UPROPERTY(EditAnywhere, Category = "Anomaly")
	TSubclassOf<class AAnomaly_Generator> Generator;

#pragma endregion

#pragma region HUD

protected:
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<class UUI_Base> UI_HUD_InGame;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<class UUI_Base> UI_HUD_MainMenu;

#pragma endregion

#pragma region KeyVal

public:
	UPROPERTY(BlueprintReadWrite, Category = "AnomalyData")
	int32 GlobalSelectedKeyIndex = 0;

#pragma endregion

};