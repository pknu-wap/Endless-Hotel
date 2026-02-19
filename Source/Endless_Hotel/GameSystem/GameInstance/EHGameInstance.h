// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/Level/Type_Level.h"
#include <CoreMinimal.h>
#include <Engine/GameInstance.h>
#include <Engine/StreamableManager.h>
#include <Delegates/DelegateCombinations.h>
#include <EHGameInstance.generated.h>

#pragma region Declare

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelLoaded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelShown);

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API UEHGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
#pragma region ASync

public:
	FStreamableManager StreamableManager;

#pragma endregion

#pragma region Level

public:
	void OpenLevel(const ELevelType& LevelName, bool bNeedLoading);
	void QuitGame();

	class ULevelStreamingDynamic* GetCurrentLevel() const { return CurrentLevel; }

public:
	static ELevelType CurrentLevelType;

protected:
	UPROPERTY()
	TObjectPtr<class ULevelStreamingDynamic> CurrentLevel;

	UPROPERTY(EditAnyWhere, Category = "Level")
	TSoftObjectPtr<UWorld> Level_MainMenu;

	UPROPERTY(EditAnyWhere, Category = "Level")
	TSoftObjectPtr<UWorld> Level_Hotel;

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
	static FLevelShown OnLevelShown;

#pragma endregion

#pragma region Anomaly

protected:
	void SpawnAnomalyGenerator();

protected:
	UPROPERTY(EditAnywhere, Category = "Anomaly")
	TSubclassOf<class AAnomaly_Generator> GeneratorClass;

	UPROPERTY()
	TObjectPtr<class AAnomaly_Generator> Generator;

#pragma endregion

#pragma region Spawn

protected:
	void RelocatePlayer();

protected:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	FTransform DefaultTransform = FTransform(FRotator::ZeroRotator, FVector(-1200, 900, 680), FVector(0.75f, 0.75f, 0.75f));

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere, Category = "Widget|HUD")
	TSubclassOf<class UUI_Base> UI_HUD_InGame;

	UPROPERTY(EditAnywhere, Category = "Widget|HUD")
	TSubclassOf<class UUI_Base> UI_HUD_MainMenu;

	UPROPERTY(EditAnywhere, Category = "Widget|Cover")
	TSubclassOf<class UUI_Base> UI_Loading;

#pragma endregion

};