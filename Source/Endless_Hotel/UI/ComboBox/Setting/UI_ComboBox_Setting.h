// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/ComboBox/UI_ComboBox_Base.h"
#include "Interface/UI/OptionInterface.h"
#include <CoreMinimal.h>
#include <UI_ComboBox_Setting.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_ComboBox_Setting : public UUI_ComboBox_Base, public IOptionInterface
{
	GENERATED_BODY()

#pragma region Interface

public:
	virtual void InitOption(EOptionCategory Category, TArray<FOptionValuePair> Values) override;

#pragma endregion

#pragma region ComboBox

public:
	virtual void OnSelectionChanged(FName NameValue, ESelectInfo::Type EnumValue) override;

#pragma endregion

#pragma region Option

private:
	void SetOption_Resolution(FName OptionValue);
	void SetOption_Grapic(FName OptionValue);
	void SetOption_Language(FName OptionValue);

private:
	EOptionCategory OptionCategory;

#pragma endregion

};