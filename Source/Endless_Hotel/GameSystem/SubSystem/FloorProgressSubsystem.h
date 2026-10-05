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
	void AdvanceFloor(const bool bPassed);
	uint8 GetFloor() const { return Floor; }
	bool GetIsFirstFloor() const { return bIsFirstStartFloor; }
	
private:
	void SubFloor();
	void AddFloor();
	void ResetFloor() { Floor = STARTFLOOR; }

public:
	DECLARE_MULTICAST_DELEGATE(FOnFloorChange_Reset);
	FOnFloorChange_Reset FloorChange_Reset;

	DECLARE_MULTICAST_DELEGATE(FOnFloorChange_Disable);
	FOnFloorChange_Disable FloorChange_Disable;

private:
	uint8 Floor = STARTFLOOR;
	bool bIsFirstStartFloor = true;
	
#pragma endregion

#pragma region Reset

public:
	void ResetFloorProgress();

#pragma endregion

#pragma region Progression

private:
	void ProgressGameState();

private:
	bool bFirstReset = true;

#pragma endregion

};