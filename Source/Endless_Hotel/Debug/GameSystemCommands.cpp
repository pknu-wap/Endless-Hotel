// Copyright by 2026-1 WAP Game 2 team

#include "GameSystem/SubSystem/GameSystem.h"
#include "Anomaly/Generator/Anomaly_Generator.h"
#include "Asset/Manager/EHAssetManager.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/HUD/InGame/UI_HUD_InGame.h"
#include <CoreMinimal.h>
#include <HAL/IConsoleManager.h>
#include <EngineUtils.h>

static FAutoConsoleCommand SetExceptClearedAnomaly(TEXT("EHDebug.GameSystem.SetExceptClearedAnomaly"), TEXT("Usage: EHDebug.GameSystem.ExceptClearedAnomaly <true|false>"), FConsoleCommandWithArgsDelegate::CreateLambda([](const TArray<FString>& Args)
	{
		if (Args.Num() != 1)
		{
			return;
		}
		auto* Subsystem = GEngine->GetCurrentPlayWorld()->GetGameInstance()->GetSubsystem<UGameSystem>();
		Subsystem->bExceptClearedAnomaly = Args[0].Equals(TEXT("true"), ESearchCase::IgnoreCase) || Args[0] == TEXT("1") ? true : false;
	}));

static FAutoConsoleCommand SetIsClear(TEXT("EHDebug.GameSystem.SetIsClear"), TEXT("Usage: EHDebug.GameSystem.IsClear <true|false>"), FConsoleCommandWithArgsDelegate::CreateLambda([](const TArray<FString>& Args)
	{
		if (Args.Num() != 1)
		{
			return;
		}
		auto* Subsystem = GEngine->GetCurrentPlayWorld()->GetGameInstance()->GetSubsystem<UGameSystem>();
		Subsystem->bIsClear = Args[0].Equals(TEXT("true"), ESearchCase::IgnoreCase) || Args[0] == TEXT("1") ? true : false;
	}));

static FAutoConsoleCommand AddAnomalyRule(TEXT("EHDebug.GameSystem.AddAnomalyRule"), TEXT("Usage: EHDebug.GameSystem.AddAnomalyRule <RuleName>"), FConsoleCommandWithArgsDelegate::CreateLambda([](const TArray<FString>& Args)
	{
		if (Args.Num() != 1)
		{
			return;
		}
		auto* Subsystem = GEngine->GetCurrentPlayWorld()->GetGameInstance()->GetSubsystem<UGameSystem>();
		const UEnum* RuleEnum = StaticEnum<EAnomalyRule>();
		uint8 RuleValue = RuleEnum->GetValueByNameString(Args[0]);
		if (RuleValue == INDEX_NONE)
		{
			RuleValue = RuleEnum->GetValueByNameString(FString::Printf(TEXT("EAnomalyRule::%s"), *Args[0]));
		}
		const EAnomalyRule Rule = static_cast<EAnomalyRule>(RuleValue);

		Subsystem->AddAnomalyRule(Rule);
	}));

static FAutoConsoleCommand AddAllAnomalyRule(TEXT("EHDebug.GameSystem.AddAllAnomalyRule"), TEXT(""), FConsoleCommandDelegate::CreateLambda([]()
	{
		auto* Subsystem = GEngine->GetCurrentPlayWorld()->GetGameInstance()->GetSubsystem<UGameSystem>();
		Subsystem->AddAnomalyRule(EAnomalyRule::Doll);
		Subsystem->AddAnomalyRule(EAnomalyRule::Painting);
		Subsystem->AddAnomalyRule(EAnomalyRule::TurnOffSound);
		Subsystem->AddAnomalyRule(EAnomalyRule::ResetObject);
	}));

static FAutoConsoleCommand RemoveAllAnomalyRule(TEXT("EHDebug.GameSystem.RemoveAllAnomalyRule"), TEXT(""), FConsoleCommandDelegate::CreateLambda([]()
	{
		auto* Subsystem = GEngine->GetCurrentPlayWorld()->GetGameInstance()->GetSubsystem<UGameSystem>();
		Subsystem->RemoveAnomalyRule(EAnomalyRule::Doll);
		Subsystem->RemoveAnomalyRule(EAnomalyRule::Painting);
		Subsystem->RemoveAnomalyRule(EAnomalyRule::TurnOffSound);
		Subsystem->RemoveAnomalyRule(EAnomalyRule::ResetObject);
	}));

static void LogAnomalyIDHint()
{
    const UEnum* IDEnum = StaticEnum<EAnomalyID>();
    FString Hint = TEXT("Available IDs: ");

    for (int32 Index = 0; Index < IDEnum->NumEnums() - 1; ++Index)
    {
        Hint += IDEnum->GetNameStringByIndex(Index);
        if (Index < IDEnum->NumEnums() - 2)
        {
            Hint += TEXT(", ");
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("%s"), *Hint);
}

static FAutoConsoleCommand AddSpawnAnomaly(
    TEXT("EHDebug.GameSystem.AddSpawnAnomaly"),
    TEXT("Usage: EHDebug.GameSystem.AddSpawnAnomaly <AnomalyID>"),
    FConsoleCommandWithArgsDelegate::CreateLambda([](const TArray<FString>& Args)
        {
            if (Args.Num() != 1)
            {
                UE_LOG(LogTemp, Warning, TEXT("Usage: EHDebug.GameSystem.AddSpawnAnomaly <AnomalyID>"));
                LogAnomalyIDHint();
                return;
            }

            const UEnum* IDEnum = StaticEnum<EAnomalyID>();
            int64 Value = IDEnum->GetValueByNameString(Args[0]);
            if (Value == INDEX_NONE)
            {
                Value = IDEnum->GetValueByNameString(FString::Printf(TEXT("EAnomalyID::%s"), *Args[0]));
            }

            if (Value == INDEX_NONE)
            {
                UE_LOG(LogTemp, Warning, TEXT("Invalid AnomalyID: %s"), *Args[0]);
                LogAnomalyIDHint();
                return;
            }

            const EAnomalyID AnomalyID = static_cast<EAnomalyID>(Value);
            auto& AssetManager = UEHAssetManager::Get();
            AssetManager.AddToSpawnList(AnomalyID);

            auto* UICon = GEngine->GetCurrentPlayWorld()->GetGameInstance()->GetSubsystem<UUI_Controller>();
            if (auto* UI_InGame = Cast<UUI_HUD_InGame>(UICon->GetHUDWidget()))
            {
                UI_InGame->ChangeDebugAnomaly();
            }
        })
);

static FAutoConsoleCommand RemoveSpawnAnomaly(
    TEXT("EHDebug.GameSystem.RemoveSpawnAnomaly"),
    TEXT("Usage: EHDebug.GameSystem.RemoveSpawnAnomaly <AnomalyID>"),
    FConsoleCommandWithArgsDelegate::CreateLambda([](const TArray<FString>& Args)
        {
            if (Args.Num() != 1)
            {
                UE_LOG(LogTemp, Warning, TEXT("Usage: EHDebug.GameSystem.RemoveSpawnAnomaly <AnomalyID>"));
                LogAnomalyIDHint();
                return;
            }

            const UEnum* IDEnum = StaticEnum<EAnomalyID>();
            int64 Value = IDEnum->GetValueByNameString(Args[0]);
            if (Value == INDEX_NONE)
            {
                Value = IDEnum->GetValueByNameString(FString::Printf(TEXT("EAnomalyID::%s"), *Args[0]));
            }

            if (Value == INDEX_NONE)
            {
                UE_LOG(LogTemp, Warning, TEXT("Invalid AnomalyID: %s"), *Args[0]);
                LogAnomalyIDHint();
                return;
            }

            const EAnomalyID AnomalyID = static_cast<EAnomalyID>(Value);
            auto& AssetManager = UEHAssetManager::Get();
            AssetManager.RemoveFromSpawnList(AnomalyID);

            auto* UICon = GEngine->GetCurrentPlayWorld()->GetGameInstance()->GetSubsystem<UUI_Controller>();
            if (auto* UI_InGame = Cast<UUI_HUD_InGame>(UICon->GetHUDWidget()))
            {
                UI_InGame->ChangeDebugAnomaly();
            }
        })
);

static FAutoConsoleCommand AddAllSpawnAnomaly(
    TEXT("EHDebug.GameSystem.AddAllSpawnAnomaly"),
    TEXT("Add all AnomalyIDs to the spawn list"),
    FConsoleCommandDelegate::CreateLambda([]()
        {
            const UEnum* IDEnum = StaticEnum<EAnomalyID>();
            auto& AssetManager = UEHAssetManager::Get();

            for (int32 Index = 0; Index < IDEnum->NumEnums() - 1; ++Index)
            {
                const EAnomalyID ID = static_cast<EAnomalyID>(IDEnum->GetValueByIndex(Index));
                AssetManager.AddToSpawnList(ID);
            }

            auto* UICon = GEngine->GetCurrentPlayWorld()->GetGameInstance()->GetSubsystem<UUI_Controller>();
            if (auto* UI_InGame = Cast<UUI_HUD_InGame>(UICon->GetHUDWidget()))
            {
                UI_InGame->ChangeDebugAnomaly();
            }
        })
);

static FAutoConsoleCommand RemoveAllSpawnAnomaly(
    TEXT("EHDebug.GameSystem.RemoveAllSpawnAnomaly"),
    TEXT("Remove all AnomalyIDs from the spawn list"),
    FConsoleCommandDelegate::CreateLambda([]()
        {
            const UEnum* IDEnum = StaticEnum<EAnomalyID>();
            auto& AssetManager = UEHAssetManager::Get();

            for (int32 Index = 0; Index < IDEnum->NumEnums() - 1; ++Index)
            {
                const EAnomalyID ID = static_cast<EAnomalyID>(IDEnum->GetValueByIndex(Index));
                AssetManager.RemoveFromSpawnList(ID);
            }

            auto* UICon = GEngine->GetCurrentPlayWorld()->GetGameInstance()->GetSubsystem<UUI_Controller>();
            if (auto* UI_InGame = Cast<UUI_HUD_InGame>(UICon->GetHUDWidget()))
            {
                UI_InGame->ChangeDebugAnomaly();
            }
        })
);

static FAutoConsoleCommand PrintSpawnAnomalyList(
    TEXT("EHDebug.GameSystem.PrintSpawnAnomalyList"),
    TEXT("Print the current active spawn anomaly list"),
    FConsoleCommandDelegate::CreateLambda([]()
        {
            auto& AssetManager = UEHAssetManager::Get();
            UE_LOG(LogTemp, Log, TEXT("[Debug] Current Spawn Anomaly List: %s"), *AssetManager.GetActAnomalyListAsString());
        })
);

static FAutoConsoleCommand SetNextAnomaly(
    TEXT("EHDebug.GameSystem.SetNextAnomaly"),
    TEXT("Usage: EHDebug.GameSystem.SetNextAnomaly <AnomalyID>"),
    FConsoleCommandWithArgsDelegate::CreateLambda([](const TArray<FString>& Args)
        {
            if (Args.Num() != 1)
            {
                UE_LOG(LogTemp, Warning, TEXT("Usage: EHDebug.GameSystem.SetNextAnomaly <AnomalyID>"));
                LogAnomalyIDHint();
                return;
            }

            const UEnum* IDEnum = StaticEnum<EAnomalyID>();
            int64 Value = IDEnum->GetValueByNameString(Args[0]);
            if (Value == INDEX_NONE)
            {
                Value = IDEnum->GetValueByNameString(FString::Printf(TEXT("EAnomalyID::%s"), *Args[0]));
            }
            if (Value == INDEX_NONE)
            {
                UE_LOG(LogTemp, Warning, TEXT("Invalid AnomalyID: %s"), *Args[0]);
                LogAnomalyIDHint();
                return;
            }

            const EAnomalyID AnomalyID = static_cast<EAnomalyID>(Value);

            if (AnomalyID == EAnomalyID::None || AnomalyID == EAnomalyID::Normal)
            {
                return;
            }

            UWorld* World = GEngine->GetCurrentPlayWorld();
            AAnomaly_Generator* Generator = nullptr;
            for (TActorIterator<AAnomaly_Generator> It(World); It; ++It)
            {
                Generator = *It;
                break;
            }
            if (Generator->SetNextAnomalyForced(AnomalyID))
            {
                auto* UICon = GEngine->GetCurrentPlayWorld()->GetGameInstance()->GetSubsystem<UUI_Controller>();
                if (auto* UI_InGame = Cast<UUI_HUD_InGame>(UICon->GetHUDWidget()))
                {
                    UI_InGame->ChangeDebugAnomaly();
                }

                UE_LOG(LogTemp, Log, TEXT("[Debug] Next anomaly forced to: %s"), *Args[0]);
            }
        })
);