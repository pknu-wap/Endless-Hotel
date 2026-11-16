// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <SteamSubsystem.generated.h>

#pragma region Declare

UENUM()
enum class EAchievementID : uint8
{
	None,
	CheckIn,
	Manual,
	NoteBook,
	PerfectClear,
	TrueEnding,
	BadEnding
};

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API USteamSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
#pragma region Achievement

public:
	void UnlockAchievement(const EAchievementID& AchID);

#pragma endregion

};