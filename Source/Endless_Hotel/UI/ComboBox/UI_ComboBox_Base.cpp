// Copyright by 2025-2 WAP Game 2 team

#include "UI/ComboBox/UI_ComboBox_Base.h"
#include "Type/UI/Type_Setting.h"
#include <Components/TextBlock.h>

#pragma region Base

void UUI_ComboBox_Base::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ComboBox->OnSelectionChanged.AddDynamic(this, &ThisClass::OnSelectionChanged);
	ComboBox->OnGenerateItemWidget.BindUFunction(this, TEXT("SetItemStyle"));
	ComboBox->OnGenerateContentWidget.BindUFunction(this, TEXT("SetItemStyle"));
}

#pragma endregion

#pragma region Generate

UWidget* UUI_ComboBox_Base::SetItemStyle(FName InKey)
{
	UEnum* EnumObj = StaticEnum<EOptionValue>();
	const int32& Index = EnumObj->GetIndexByName(InKey);
	const EOptionValue& EnumValue = static_cast<EOptionValue>(EnumObj->GetValueByIndex(Index));

	UTextBlock* TextBlock = NewObject<UTextBlock>(ComboBox);
	TextBlock->SetText(EnumObj->GetDisplayNameTextByIndex(Index));
	TextBlock->SetFont(Font_ComboBox);
	TextBlock->SetColorAndOpacity(ComboBox->GetForegroundColor());

	return TextBlock;
}

#pragma endregion