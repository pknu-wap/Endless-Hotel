// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Setting/UI_PopUp_Option_Screen.h"
#include "Type/UI/Type_UI_Setting.h"
#include <Components/ComboBoxKey.h>
#include <Components/TextBlock.h>

#pragma region Base

void UUI_PopUp_Option_Screen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Combo_Resolution->ClearOptions();
	Combo_Resolution->AddOption(EnumObj->GetNameByValue(static_cast<int64>(EOptionValue::HD)));
	Combo_Resolution->AddOption(EnumObj->GetNameByValue(static_cast<int64>(EOptionValue::FHD)));
	Combo_Resolution->AddOption(EnumObj->GetNameByValue(static_cast<int64>(EOptionValue::QHD)));
	Combo_Resolution->AddOption(EnumObj->GetNameByValue(static_cast<int64>(EOptionValue::UHD)));
}

void UUI_PopUp_Option_Screen::NativeConstruct()
{
	Super::NativeConstruct();

	Combo_Resolution->OnGenerateItemWidget.Clear();
	Combo_Resolution->OnGenerateItemWidget.BindUFunction(this, TEXT("GenerateResolutionItem"));

	Combo_Resolution->OnGenerateContentWidget.Clear();
	Combo_Resolution->OnGenerateContentWidget.BindUFunction(this, TEXT("GenerateResolutionItem"));

	RestoreOptions();
}

#pragma endregion

#pragma region Restore

void UUI_PopUp_Option_Screen::RestoreOptions()
{
	// 임시로 값 하드코딩 함, 추후에 설정 값 복원 기능 추가 시 변경 예정
	Combo_Resolution->SetSelectedOption(EnumObj->GetNameByValue(static_cast<int64>(EOptionValue::FHD)));
}

#pragma endregion

#pragma region Resolution

UWidget* UUI_PopUp_Option_Screen::GenerateResolutionItem(FName InKey)
{
	const int32 Index = EnumObj->GetIndexByName(InKey);
	const EOptionValue EnumValue = static_cast<EOptionValue>(EnumObj->GetValueByIndex(Index));

	UTextBlock* TextBlock = NewObject<UTextBlock>(this);
	FText ContentText = FText::FromString(TEXT("Error"));

	switch (EnumValue)
	{
	case EOptionValue::HD:
		ContentText = FText::FromString(TEXT("1280 X 720 (HD)"));
		break;

	case EOptionValue::FHD:
		ContentText = FText::FromString(TEXT("1920 X 1080 (FHD)"));
		break;

	case EOptionValue::QHD:
		ContentText = FText::FromString(TEXT("2560 X 1440 (QHD)"));
		break;

	case EOptionValue::UHD:
		ContentText = FText::FromString(TEXT("3840 X 2160 (UHD)"));
		break;
	}

	TextBlock->SetText(ContentText);
	TextBlock->SetFont(ComboBoxFont);
	TextBlock->SetColorAndOpacity(Combo_Resolution->GetForegroundColor());

	return TextBlock;
}

#pragma endregion