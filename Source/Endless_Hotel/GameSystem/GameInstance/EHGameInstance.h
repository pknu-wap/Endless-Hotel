// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/Level/Type_Level.h"
#include <Engine/GameInstance.h>
#include <Delegates/DelegateCombinations.h>
#include <EHGameInstance.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UEHGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
#pragma region Game

public:
	void QuitGame();

#pragma endregion

#pragma region Level

public:
	void OpenLevel(const ELevelType& LevelName, bool bNeedLoading);

public:
	ELevelType CurrentLevelType = ELevelType::Persistent;

protected:
	UPROPERTY(EditAnyWhere, Category = "Level")
	TSoftObjectPtr<UWorld> Level_MainMenu;

	UPROPERTY(EditAnyWhere, Category = "Level")
	TSoftObjectPtr<UWorld> Level_Hotel;

private:
	UPROPERTY()
	TObjectPtr<ULevelStreaming> CurrentStreamLevel;

	UPROPERTY()
	TSoftObjectPtr<UWorld> CurrentLevel;

	bool bIsOpenedLoadingWidget = false;

#pragma endregion

#pragma region Loading

public:
	bool IsLevelLoaded();

private:
	void LoadStreamLevel();

	UFUNCTION()
	void OnLevelLoaded();

	UFUNCTION()
	void OnLevelShown();

private:
	void UnloadStreamLevel();

	UFUNCTION()
	void OnLevelUnloaded();

private:
	void StartLoadedLevel();

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelShown);
	FLevelShown LevelShown;

private:
	FTimerHandle StartHandle;

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

#pragma region Player

private:
	void RelocatePlayer();

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

private:
	UPROPERTY()
	TWeakObjectPtr<class UUI_PopUp_Loading> UI_Loading;

#pragma endregion

#pragma region Spawn

public:
	template<class ActorClass>
	ActorClass* SpawnActor(UClass* Class, const FVector& Location = FVector::ZeroVector, const FRotator& Rotation = FRotator::ZeroRotator)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.OverrideLevel = CurrentStreamLevel->GetLoadedLevel();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		return GetWorld()->SpawnActor<ActorClass>(Class, Location, Rotation, SpawnParams);
	}

#pragma endregion

};