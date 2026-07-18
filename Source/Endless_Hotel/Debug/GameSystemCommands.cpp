// Copyright by 2026-1 WAP Game 2 team

#include "GameSystem/SubSystem/GameSystem.h"
#include <CoreMinimal.h>
#include <HAL/IConsoleManager.h>

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