// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/Button/UI_Button_Base.h"
#include "Type/UI/Type_Setting.h"
#include <CoreMinimal.h>
#include <UI_Button_Setting.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Button_Setting : public UUI_Button_Base
{
	GENERATED_BODY()

#pragma region Option

public:
	void InitOption(FOptionData OptionData);

#pragma endregion

#pragma region HorizontalBox

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UHorizontalBox> HorizontalBox;

#pragma endregion

#pragma region TextBlock

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextBlock;

#pragma endregion

};