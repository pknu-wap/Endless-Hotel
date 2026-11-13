// Copyright by 2026-1 WAP Game 2 team

#include "GameSystem/SubSystem/SteamSubsystem.h"
#include "GameSystem/Enum/EnumConverter.h"
#include <OnlineSubsystem.h>
#include <Interfaces/OnlineIdentityInterface.h>
#include <Interfaces/OnlineAchievementsInterface.h>

#pragma region Achievement

void USteamSubsystem::UnlockAchievement(const EAchievementID& AchID)
{
    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
    IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
    FUniqueNetIdPtr UserID = Identity->GetUniquePlayerId(0);
    if (!UserID.IsValid())
    {
        return;
    }

    FOnlineAchievementsWriteRef WriteObject = MakeShared<FOnlineAchievementsWrite>();
    WriteObject->SetFloatStat(EnumConverter::GetNameFromEnum<EAchievementID>(AchID), 100.0f);

    IOnlineAchievementsPtr Achievements = Subsystem->GetAchievementsInterface();
    Achievements->WriteAchievements(*UserID, WriteObject);
}

#pragma endregion