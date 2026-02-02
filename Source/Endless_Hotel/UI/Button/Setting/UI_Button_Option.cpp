// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/Setting/UI_Button_Option.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/PopUp/Setting/UI_PopUp_Setting.h"
#include "Player/Character/EHPlayer.h"
#include "Type/Save/Type_Save.h"
#include <GameFramework/GameUserSettings.h>
#include <GameFramework/Character.h>
#include <Camera/CameraComponent.h>
#include <Kismet/GameplayStatics.h>

#pragma region Declare

FHighlightOption UUI_Button_Option::HighlightOption;

#pragma endregion

#pragma region Base

TSharedRef<SWidget> UUI_Button_Option::RebuildWidget()
{
	SettingHandle = UGameUserSettings::GetGameUserSettings();

	HighlightOption.AddDynamic(this, &ThisClass::Highlight);
	OnClicked.AddDynamic(this, &ThisClass::Click_Button);

	return Super::RebuildWidget();
}

void UUI_Button_Option::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	HighlightOption.Clear();
	OnClicked.Clear();
}

#pragma endregion

#pragma region Click

void UUI_Button_Option::Click_Button()
{
	auto* UI_Setting = GetTypedOuter<UUI_PopUp_Setting>();
	FSaveData_Setting& Data = UI_Setting->Data_Setting;

	switch (OptionInfo.Category)
	{
	// Screen Category
	case EOptionCategory::Window:
		SetOption_Window();
		Data.Window = OptionInfo.Value;
		break;

	case EOptionCategory::Aspect:
		SetOption_Aspect();
		Data.Aspect = OptionInfo.Value;
		break;

	case EOptionCategory::Frame:
		SetOption_Frame();
		Data.Frame = OptionInfo.Value;
		break;

	case EOptionCategory::VSync:
		SetOption_VSync();
		Data.VSync = OptionInfo.Value;
		break;

	case EOptionCategory::HDR:
		SetOption_HDR();
		Data.HDR = OptionInfo.Value;
		break;

	// Grapic Category
	case EOptionCategory::AntiAliasing:
		SetOption_AntiAliasing();
		Data.AntiAliasing = OptionInfo.Value;
		break;

	case EOptionCategory::Shadow:
		SetOption_Shadow();
		Data.Shadow = OptionInfo.Value;
		break;

	case EOptionCategory::Texture:
		SetOption_Texture();
		Data.Texture = OptionInfo.Value;
		break;

	case EOptionCategory::PostProcessing:
		SetOption_PostProcessing();
		Data.PostProcessing = OptionInfo.Value;
		break;

	case EOptionCategory::Shading:
		SetOption_Shading();
		Data.Shading = OptionInfo.Value;
		break;

	// Gameplay Category
	case EOptionCategory::Overlap:
		SetOption_AnomalyOverlap();
		Data.Overlap = OptionInfo.Value;
		break;

	// System Category
	case EOptionCategory::Reset_Note:
		PopUpOption_ResetNote();
		break;

	case EOptionCategory::Reset_Setting:
		PopUpOption_ResetSetting();
		break;
	}

	HighlightOption.Broadcast(OptionInfo);
}

#pragma endregion

#pragma region Highlight

void UUI_Button_Option::Highlight(FOptionInfo TargetInfo)
{
	if (OptionInfo.Category != TargetInfo.Category)
	{
		return;
	}

	FButtonStyle ButtonStyle = GetStyle();
	ButtonStyle.Normal.TintColor = Color_Default;

	if (OptionInfo.Value == TargetInfo.Value)
	{
		ButtonStyle.Normal.TintColor = Color_Highlight;
	}

	SetStyle(ButtonStyle);
}

#pragma endregion

#pragma region Screen

void UUI_Button_Option::SetOption_Window()
{
	switch (OptionInfo.Value)
	{
	case EOptionValue::Windowed:
		SettingHandle->SetFullscreenMode(EWindowMode::Windowed);
		break;

	case EOptionValue::FullScreen:
		SettingHandle->SetFullscreenMode(EWindowMode::Fullscreen);
		break;

	case EOptionValue::WindowedFullScreen:
		SettingHandle->SetFullscreenMode(EWindowMode::WindowedFullscreen);
		break;
	}
}

void UUI_Button_Option::SetOption_Aspect()
{
	auto* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//auto* CC = Player->Camera;

	switch (OptionInfo.Value)
	{
	case EOptionValue::W16H9:
		//CC->SetAspectRatio(16.0f / 9.0f);
		break;

	case EOptionValue::W21H9:
		//CC->SetAspectRatio(21.0f / 9.0f);
		break;

	case EOptionValue::W4H3:
		//CC->SetAspectRatio(4.0f / 3.0f);
		break;

	case EOptionValue::W16H10:
		//CC->SetAspectRatio(16.0f / 10.0f);
		break;
	}
}

void UUI_Button_Option::SetOption_Frame()
{
	switch (OptionInfo.Value)
	{
	case EOptionValue::Low:
		GEngine->SetMaxFPS(60);
		break;

	case EOptionValue::Medium:
		GEngine->SetMaxFPS(120);
		break;

	case EOptionValue::High:
		GEngine->SetMaxFPS(144);
		break;

	case EOptionValue::Epic:
		GEngine->SetMaxFPS(240);
		break;
	}
}

void UUI_Button_Option::SetOption_VSync()
{
	switch (OptionInfo.Value)
	{
	case EOptionValue::On:
		SettingHandle->SetVSyncEnabled(true);
		break;

	case EOptionValue::Off:
		SettingHandle->SetVSyncEnabled(false);
		break;
	}
}

void UUI_Button_Option::SetOption_HDR()
{
	switch (OptionInfo.Value)
	{
	case EOptionValue::On:
		SettingHandle->EnableHDRDisplayOutput(true);
		break;

	case EOptionValue::Off:
		SettingHandle->EnableHDRDisplayOutput(false);
		break;
	}
}

#pragma endregion

#pragma region Grapic

void UUI_Button_Option::SetOption_AntiAliasing()
{
	SettingHandle->SetAntiAliasingQuality(static_cast<int32>(OptionInfo.Value));
}

void UUI_Button_Option::SetOption_Shadow()
{
	SettingHandle->SetShadowQuality(static_cast<int32>(OptionInfo.Value));
}

void UUI_Button_Option::SetOption_Texture()
{
	SettingHandle->SetTextureQuality(static_cast<int32>(OptionInfo.Value));
}

void UUI_Button_Option::SetOption_PostProcessing()
{
	SettingHandle->SetPostProcessingQuality(static_cast<int32>(OptionInfo.Value));
}

void UUI_Button_Option::SetOption_Shading()
{
	SettingHandle->SetShadingQuality(static_cast<int32>(OptionInfo.Value));
}

#pragma endregion

#pragma region Gameplay

void UUI_Button_Option::SetOption_AnomalyOverlap()
{
	switch (OptionInfo.Value)
	{
	case EOptionValue::On:
		// 여기에 중복 제거 코드 (담당: 경원 김)
		break;

	case EOptionValue::Off:
		// 여기에 중복 가능 코드 (담당: 경원 김)
		break;
	}
}

#pragma endregion

#pragma region System

void UUI_Button_Option::PopUpOption_ResetNote()
{
	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(UI_ResetNote);
}

void UUI_Button_Option::PopUpOption_ResetSetting()
{
	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(UI_ResetSetting);
}

#pragma endregion