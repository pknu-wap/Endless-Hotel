// Copyright by 2025-2 WAP Game 2 team

#include "UI/ComboBox/UI_ComboBox_Base.h"
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
	UTextBlock* TextBlock = NewObject<UTextBlock>(ComboBox);
	if (const FText* Text = Translations.Find(InKey))
	{
		TextBlock->SetText(*Text);
	}
	TextBlock->SetFont(Font_Style);
	TextBlock->SetColorAndOpacity(Font_Color);

	return TextBlock;
}

#pragma endregion