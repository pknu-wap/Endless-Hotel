// Copyright by 2025-2 WAP Game 2 team

#include "UI/HUD/Title/UI_HUD_Title.h"
#include "UI/Controller/UI_Controller.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include <Components/Image.h>
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>

#pragma region Base

void UUI_HUD_Title::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Start->OnClicked.AddDynamic(this, &ThisClass::Click_Start);
	Button_Setting->OnClicked.AddDynamic(this, &ThisClass::Click_Setting);
	Button_Quit->OnClicked.AddDynamic(this, &ThisClass::Click_Quit);
}

void UUI_HUD_Title::NativeConstruct()
{
	Super::NativeConstruct();

	SetLogoImage();
}

#pragma endregion

#pragma region Click

void UUI_HUD_Title::Click_Start()
{
	auto* Subsystem = GetGameInstance()->GetSubsystem<UGameSystem>();
	Subsystem->bIsClear = false;
	Subsystem->Floor = 9;

	UEHGameInstance* GameInstance = GetGameInstance<UEHGameInstance>();
	GameInstance->OpenLevel(ELevelType::Hotel, true);
}

void UUI_HUD_Title::Click_Setting()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(UI_Setting);
}

void UUI_HUD_Title::Click_Quit()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(UI_QuitCheck);
}

#pragma endregion

#pragma region Hover

void UUI_HUD_Title::PlayButtonAnim_Hover(ETitleButtonType ButtonType)
{
	switch (ButtonType)
	{
	case ETitleButtonType::Start:
		PlayAnimation(Anim_Hover_Start);
		break;

	case ETitleButtonType::Setting:
		PlayAnimation(Anim_Hover_Setting);
		break;

	case ETitleButtonType::Quit:
		PlayAnimation(Anim_Hover_Quit);
		break;
	}
}

void UUI_HUD_Title::PlayButtonAnim_Unhover(ETitleButtonType ButtonType)
{
	switch (ButtonType)
	{
	case ETitleButtonType::Start:
		PlayAnimation(Anim_Unhover_Start);
		break;

	case ETitleButtonType::Setting:
		PlayAnimation(Anim_Unhover_Setting);
		break;

	case ETitleButtonType::Quit:
		PlayAnimation(Anim_Unhover_Quit);
		break;
	}
}

#pragma endregion

#pragma region Title

void UUI_HUD_Title::SetLogoImage()
{
	if (!USaveManager::LoadData_GameClear())
	{
		return;
	}

	Image_Logo->SetBrushFromTexture(Texture_Clear);
}

#pragma endregion