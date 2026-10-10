// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Type/Save/Type_Save.h"
#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <Delegates/DelegateCombinations.h>
#include <GameSystem.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UGameSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

#pragma region Base

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

#pragma endregion

#pragma region Choose

public:
	uint8 ChooseKeyIndex = 0;

#pragma endregion

#pragma region Reset

public:
	void ResetGameSystem() const;

#pragma endregion

#pragma region Progression

public:
	void ChangeProgression(EGameProgression Target);
	EGameProgression GetGameProgression() const { return GameProgression; }

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnProgressionChanged, EGameProgression);
	FOnProgressionChanged OnProgressionChanged;
	
private:
	EGameProgression GameProgression = EGameProgression::Tutorial;

#pragma endregion
	
#pragma region Clear

public:
	void GameClear();
	bool IsGameClear() const;

public:
	DECLARE_MULTICAST_DELEGATE(FGameClearEvent);
	FGameClearEvent GameClearEvent;

#pragma endregion

};