// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/Setting/UI_Button_Key.h"
#include "Player/Controller/EHPlayerController.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include <Kismet/GameplayStatics.h>
#include <Components/InputKeySelector.h>

#pragma region Base

void UUI_Button_Key::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Selector->OnKeySelected.AddDynamic(this, &ThisClass::SelectedKeyValue);
	Button->OnClicked.AddDynamic(this, &ThisClass::ResetInputButtons);
}

#pragma endregion

#pragma region Reset

void UUI_Button_Key::ResetInputButtons()
{
	USaveManager::LoadData_Setting().ResetKeySetting();

	auto* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PC->SetKeyMapping(SettingInfo, FKey());

	SelectedKeyValue(FInputChord(SettingInfo.Value));
}

#pragma endregion

#pragma region Selector

void UUI_Button_Key::SelectedKeyValue(FInputChord SelectedChord)
{
	SettingInfo.Value = SelectedChord.Key;

	FSaveData_Setting Data = USaveManager::LoadData_Setting();

	auto* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	switch (SettingInfo.Type)
	{
	case EKeySettingType::Up:
		PC->SetKeyMapping(SettingInfo, Data.Up.Value);
		Data.Up = SettingInfo;
		Selector->SetSelectedKey(FInputChord(Data.Up.Value));
		break;

	case EKeySettingType::Down:
		PC->SetKeyMapping(SettingInfo, Data.Down.Value);
		Data.Down = SettingInfo;
		Selector->SetSelectedKey(FInputChord(Data.Down.Value));
		break;

	case EKeySettingType::Left:
		PC->SetKeyMapping(SettingInfo, Data.Left.Value);
		Data.Left = SettingInfo;
		Selector->SetSelectedKey(FInputChord(Data.Left.Value));
		break;

	case EKeySettingType::Right:
		PC->SetKeyMapping(SettingInfo, Data.Right.Value);
		Data.Right = SettingInfo;
		Selector->SetSelectedKey(FInputChord(Data.Right.Value));
		break;

	case EKeySettingType::Run:
		PC->SetKeyMapping(SettingInfo, Data.Run.Value);
		Data.Run = SettingInfo;
		Selector->SetSelectedKey(FInputChord(Data.Run.Value));
		break;

	case EKeySettingType::Sit:
		PC->SetKeyMapping(SettingInfo, Data.Sit.Value);
		Data.Sit = SettingInfo;
		Selector->SetSelectedKey(FInputChord(Data.Sit.Value));
		break;

	case EKeySettingType::Interact:
		PC->SetKeyMapping(SettingInfo, Data.Interact.Value);
		Data.Interact = SettingInfo;
		Selector->SetSelectedKey(FInputChord(Data.Interact.Value));
		break;

	case EKeySettingType::Hide:
		PC->SetKeyMapping(SettingInfo, Data.Hide.Value);
		Data.Hide = SettingInfo;
		Selector->SetSelectedKey(FInputChord(Data.Hide.Value));
		break;

	case EKeySettingType::Lighter:
		PC->SetKeyMapping(SettingInfo, Data.Lighter.Value);
		Data.Lighter = SettingInfo;
		Selector->SetSelectedKey(FInputChord(Data.Lighter.Value));
		break;
	}
	
	USaveManager::SaveData_Setting(Data);
}

#pragma endregion