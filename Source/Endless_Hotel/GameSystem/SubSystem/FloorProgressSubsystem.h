// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <Delegates/DelegateCombinations.h>
#include <FloorProgressSubsystem.generated.h>

#define STARTFLOOR 8

UCLASS()
class ENDLESS_HOTEL_API UFloorProgressSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

#pragma region Base

public:
	UFloorProgressSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

#pragma endregion

#pragma region Floor

public:
	void ResetFloor();
	void SubFloor();
	void AddFloor();

	uint8 GetFloor() const { return Floor; }

public:
	uint8 Floor = STARTFLOOR;
	bool bIsFirstStartFloor = true;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFloorChange_Reset);
	FOnFloorChange_Reset FloorChange_Reset;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFloorChange_Disable);
	FOnFloorChange_Disable FloorChange_Disable;

#pragma endregion

#pragma region Clear

public:
	UFUNCTION()
	void GameClear();

	bool IsGameClear() const { return bIsClear; }

public:
	bool bIsClear = false;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameClearEvent);
	FGameClearEvent GameClearEvent;

#pragma endregion

#pragma region Reset

public:
	void ResetFloorProgress();

#pragma endregion
};