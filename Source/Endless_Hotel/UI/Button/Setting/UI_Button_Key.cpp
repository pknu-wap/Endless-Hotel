// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/Setting/UI_Button_Key.h"
#include "Player/Controller/EHPlayerController.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include <Kismet/GameplayStatics.h>
#include <Components/InputKeySelector.h>

#pragma region Declare

FKeyHighlight UUI_Button_Key::Highlight;

#pragma endregion

#pragma region Bind

void UUI_Button_Key::BindEvents()
{
	for (auto* Check : GetAllChildren())
	{
		if (auto* Target = Cast<UInputKeySelector>(Check))
		{
			Selector = Target;
			break;
		}
	}

	if (Selector)
	{
		Selector->OnKeySelected.RemoveDynamic(this, &ThisClass::SelectedKeyValue);
		Selector->OnKeySelected.AddDynamic(this, &ThisClass::SelectedKeyValue);
	}

	OnClicked.RemoveDynamic(this, &ThisClass::Click_Button);
	OnClicked.AddDynamic(this, &ThisClass::Click_Button);

	Highlight.RemoveDynamic(this, &ThisClass::SetSavedOption);
	Highlight.AddDynamic(this, &ThisClass::SetSavedOption);
}

#pragma endregion

#pragma region Click

void UUI_Button_Key::Click_Button()
{
	FSaveData_Key Data = FSaveData_Key();
	USaveManager::SaveKeyData(Data);

	auto* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PC->SetKeyMapping(SettingInfo);

	Highlight.Broadcast();
}

#pragma endregion

#pragma region Selector

void UUI_Button_Key::SelectedKeyValue(FInputChord SelectedChord)
{
	SettingInfo.Value = SelectedChord.Key;

	FSaveData_Key Data = USaveManager::LoadKeyData();

	auto* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PC->SetKeyMapping(SettingInfo);

	switch (SettingInfo.Type)
	{
	case EKeySettingType::Up:
		Data.Up = SettingInfo;
		break;

	case EKeySettingType::Down:
		Data.Down = SettingInfo;
		break;

	case EKeySettingType::Left:
		Data.Left = SettingInfo;
		break;

	case EKeySettingType::Right:
		Data.Right = SettingInfo;
		break;

	case EKeySettingType::Run:
		Data.Run = SettingInfo;
		break;

	case EKeySettingType::Sit:
		Data.Sit = SettingInfo;
		break;

	case EKeySettingType::Interact:
		Data.Interact = SettingInfo;
		break;

	case EKeySettingType::Hide:
		Data.Hide = SettingInfo;
		break;

	case EKeySettingType::Flash:
		Data.Flash = SettingInfo;
		break;
	}

	USaveManager::SaveKeyData(Data);
}

#pragma endregion

#pragma region Highlight

void UUI_Button_Key::SetSavedOption()
{
	FSaveData_Key Data = USaveManager::LoadKeyData();
	
	switch (SettingInfo.Type)
	{
	case EKeySettingType::Up:
		Selector->SetSelectedKey(FInputChord(Data.Up.Value));
		break;

	case EKeySettingType::Down:
		Selector->SetSelectedKey(FInputChord(Data.Down.Value));
		break;

	case EKeySettingType::Left:
		Selector->SetSelectedKey(FInputChord(Data.Left.Value));
		break;

	case EKeySettingType::Right:
		Selector->SetSelectedKey(FInputChord(Data.Right.Value));
		break;

	case EKeySettingType::Run:
		Selector->SetSelectedKey(FInputChord(Data.Run.Value));
		break;

	case EKeySettingType::Sit:
		Selector->SetSelectedKey(FInputChord(Data.Sit.Value));
		break;

	case EKeySettingType::Interact:
		Selector->SetSelectedKey(FInputChord(Data.Interact.Value));
		break;

	case EKeySettingType::Hide:
		Selector->SetSelectedKey(FInputChord(Data.Hide.Value));
		break;

	case EKeySettingType::Flash:
		Selector->SetSelectedKey(FInputChord(Data.Flash.Value));
		break;
	}
}

#pragma endregion