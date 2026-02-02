// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/Setting/UI_Button_Option.h"
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

	OnClicked.Clear();
	OnClicked.AddDynamic(this, &ThisClass::Click_Button);

	return Super::RebuildWidget();
}

void UUI_Button_Option::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	HighlightOption.Clear();
}

#pragma endregion

#pragma region Click

void UUI_Button_Option::Click_Button()
{
	switch (OptionInfo.Category)
	{
	// Screen Category
	case EOptionCategory::Window:
		SetOption_Window();
		break;

	case EOptionCategory::Aspect:
		SetOption_Aspect();
		break;

	case EOptionCategory::Frame:
		SetOption_Frame();
		break;

	case EOptionCategory::VSync:
		SetOption_VSync();
		break;

	case EOptionCategory::HDR:
		SetOption_HDR();
		break;

	// Grapic Category
	case EOptionCategory::AntiAliasing:
		SetOption_AntiAliasing();
		break;

	case EOptionCategory::Shadow:
		SetOption_Shadow();
		break;

	case EOptionCategory::Texture:
		SetOption_Texture();
		break;

	case EOptionCategory::PostProcessing:
		SetOption_PostProcessing();
		break;

	case EOptionCategory::Shading:
		SetOption_Shading();
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
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto* CC = Player->FindComponentByClass<UCameraComponent>();

	switch (OptionInfo.Value)
	{
	case EOptionValue::W16H9:
		CC->SetAspectRatio(16.0f / 9.0f);
		break;

	case EOptionValue::W21H9:
		CC->SetAspectRatio(21.0f / 9.0f);
		break;

	case EOptionValue::W4H3:
		CC->SetAspectRatio(4.0f / 3.0f);
		break;

	case EOptionValue::W16H10:
		CC->SetAspectRatio(16.0f / 10.0f);
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