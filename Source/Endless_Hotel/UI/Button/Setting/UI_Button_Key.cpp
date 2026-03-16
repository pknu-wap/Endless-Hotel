// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/Setting/UI_Button_Key.h"
#include "Player/Controller/EHPlayerController.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include <Kismet/GameplayStatics.h>
#include <Components/InputKeySelector.h>

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
}

#pragma endregion

#pragma region Selector

void UUI_Button_Key::SelectedKeyValue(FInputChord SelectedChord)
{
	SettingInfo.Value = SelectedChord.Key;

	FSaveData_Key Data = USaveManager::LoadKeyData();

	auto* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	switch (SettingInfo.Type)
	{
	case EKeySettingType::Up:
		PC->SetKeyMapping(SettingInfo, Data.Up.Value);
		Data.Up = SettingInfo;
		break;

	case EKeySettingType::Down:
		PC->SetKeyMapping(SettingInfo, Data.Down.Value);
		Data.Down = SettingInfo;
		break;

	case EKeySettingType::Left:
		PC->SetKeyMapping(SettingInfo, Data.Left.Value);
		Data.Left = SettingInfo;
		break;

	case EKeySettingType::Right:
		PC->SetKeyMapping(SettingInfo, Data.Right.Value);
		Data.Right = SettingInfo;
		break;

	case EKeySettingType::Run:
		PC->SetKeyMapping(SettingInfo, Data.Run.Value);
		Data.Run = SettingInfo;
		break;

	case EKeySettingType::Sit:
		PC->SetKeyMapping(SettingInfo, Data.Sit.Value);
		Data.Sit = SettingInfo;
		break;

	case EKeySettingType::Interact:
		PC->SetKeyMapping(SettingInfo, Data.Interact.Value);
		Data.Interact = SettingInfo;
		break;

	case EKeySettingType::Hide:
		PC->SetKeyMapping(SettingInfo, Data.Hide.Value);
		Data.Hide = SettingInfo;
		break;

	case EKeySettingType::Flash:
		PC->SetKeyMapping(SettingInfo, Data.Flash.Value);
		Data.Flash = SettingInfo;
		break;
	}
	
	USaveManager::SaveKeyData(Data);

	ConvertLongText(SelectedChord);
}

void UUI_Button_Key::ConvertLongText(FInputChord SelectedChord)
{
	FKey Key = SelectedChord.Key;
	FText Target = Selector->GetNoKeySpecifiedText();

	if (Key == EKeys::LeftShift)
	{
		Target = FText::FromString(TEXT("LS"));
	}
	else if (Key == EKeys::RightShift)
	{
		Target = FText::FromString(TEXT("RS"));
	}
	else if (Key == EKeys::LeftControl)
	{
		Target = FText::FromString(TEXT("LC"));
	}
	else if (Key == EKeys::RightControl)
	{
		Target = FText::FromString(TEXT("RC"));
	}
	else if (Key == EKeys::RightShift)
	{
		Target = FText::FromString(TEXT("RS"));
	}
	else if (Key == EKeys::LeftAlt)
	{
		Target = FText::FromString(TEXT("LA"));
	}
	else if (Key == EKeys::RightAlt)
	{
		Target = FText::FromString(TEXT("RA"));
	}
	else if (Key == EKeys::LeftMouseButton)
	{
		Target = FText::FromString(TEXT("LMB"));
	}
	else if (Key == EKeys::RightMouseButton)
	{
		Target = FText::FromString(TEXT("RMB"));
	}
	else if (Key == EKeys::MiddleMouseButton)
	{
		Target = FText::FromString(TEXT("MMB"));
	}

	Selector->SetNoKeySpecifiedText(Target);
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