// Copyright by 2025-2 WAP Game 2 team

#include "UI/ComboBox/UI_ComboBox_Base.h"
#include "Type/UI/Type_UI_Setting.h"
#include <Components/TextBlock.h>

#pragma region Generate

void UUI_ComboBox_Base::BindEvents()
{
	OnOpening.Clear();
	OnOpening.AddDynamic(this, &ThisClass::ActiveComboBox);

	OnSelectionChanged.Clear();
	OnSelectionChanged.AddDynamic(this, &ThisClass::DeactiveComboBox);

	OnGenerateItemWidget.Clear();
	OnGenerateItemWidget.BindUFunction(this, TEXT("GenerateItem"));

	OnGenerateContentWidget.Clear();
	OnGenerateContentWidget.BindUFunction(this, TEXT("GenerateItem"));
}

UWidget* UUI_ComboBox_Base::GenerateItem(FName InKey)
{
	UEnum* EnumObj = StaticEnum<EOptionValue>();
	const int32& Index = EnumObj->GetIndexByName(InKey);
	const EOptionValue& EnumValue = static_cast<EOptionValue>(EnumObj->GetValueByIndex(Index));

	UTextBlock* TextBlock = NewObject<UTextBlock>(this);
	TextBlock->SetText(EnumObj->GetDisplayNameTextByIndex(Index));
	TextBlock->SetFont(Font_ComboBox);
	TextBlock->SetColorAndOpacity(GetForegroundColor());

	return TextBlock;
}

#pragma endregion