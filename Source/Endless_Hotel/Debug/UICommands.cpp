// Copyright by 2026-1 WAP Game 2 team

#include "UI/Controller/UI_Controller.h"
#include "UI/HUD/InGame/UI_HUD_InGame.h"
#include <CoreMinimal.h>
#include <HAL/IConsoleManager.h>

static FAutoConsoleCommand CmdShowHUD(TEXT("EHDebug.UI.Show.HUD"), TEXT(""), FConsoleCommandDelegate::CreateLambda([]()
	{
		auto* UICon = GEngine->GetCurrentPlayWorld()->GetGameInstance()->GetSubsystem<UUI_Controller>();
		UICon->ShowHUDWidget(true);
	}));

static FAutoConsoleCommand CmdHideHUD(TEXT("EHDebug.UI.Hide.HUD"), TEXT(""), FConsoleCommandDelegate::CreateLambda([]()
	{
		auto* UICon = GEngine->GetCurrentPlayWorld()->GetGameInstance()->GetSubsystem<UUI_Controller>();
		UICon->ShowHUDWidget(false);
	}));

static FAutoConsoleCommand CmdShowPopUp(TEXT("EHDebug.UI.Show.PopUp"), TEXT(""), FConsoleCommandDelegate::CreateLambda([]()
	{
		auto* UICon = GEngine->GetCurrentPlayWorld()->GetGameInstance()->GetSubsystem<UUI_Controller>();
		UICon->ShowPopUpWidget(true);
	}));

static FAutoConsoleCommand CmdHidePopUp(TEXT("EHDebug.UI.Hide.PopUp"), TEXT(""), FConsoleCommandDelegate::CreateLambda([]()
	{
		auto* UICon = GEngine->GetCurrentPlayWorld()->GetGameInstance()->GetSubsystem<UUI_Controller>();
		UICon->ShowPopUpWidget(false);
	}));

static FAutoConsoleCommand CmdShowGameInfo(TEXT("EHDebug.UI.Show.GameInfo"), TEXT(""), FConsoleCommandDelegate::CreateLambda([]()
	{
		auto* UICon = GEngine->GetCurrentPlayWorld()->GetGameInstance()->GetSubsystem<UUI_Controller>();
		if (auto* UI_InGame = Cast<UUI_HUD_InGame>(UICon->GetHUDWidget()))
		{
			UI_InGame->ShowDebugGameInfo(true);
		}
	}));

static FAutoConsoleCommand CmdHideGameInfo(TEXT("EHDebug.UI.Hide.GameInfo"), TEXT(""), FConsoleCommandDelegate::CreateLambda([]()
	{
		auto* UICon = GEngine->GetCurrentPlayWorld()->GetGameInstance()->GetSubsystem<UUI_Controller>();
		if (auto* UI_InGame = Cast<UUI_HUD_InGame>(UICon->GetHUDWidget()))
		{
			UI_InGame->ShowDebugGameInfo(false);
		}
	}));