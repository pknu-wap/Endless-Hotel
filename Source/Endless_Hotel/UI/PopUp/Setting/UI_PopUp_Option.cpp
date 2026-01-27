// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Setting/UI_PopUp_Option.h"
#include "UI/ComboBox/Setting/UI_ComboBox_Setting.h"

#pragma region Base

void UUI_PopUp_Option::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ComboBox_Default = Cast<UUI_ComboBox_Setting>(GetWidgetFromName(TEXT("ComboBox")));

	if (ComboBox_Default)
	{
		ComboBox_Default->ClearOptions();

		for (auto Value : ComboBoxOptions)
		{
			ComboBox_Default->AddEnumOption<EOptionValue>(Value);
		}
	}
}

void UUI_PopUp_Option::NativeConstruct()
{
	Super::NativeConstruct();

	if (ComboBox_Default)
	{
		ComboBox_Default->BindEvents();
	}
}

#pragma endregion