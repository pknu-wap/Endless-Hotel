// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/ComboBox/UI_ComboBox_Base.h"
#include "Type/UI/Type_Setting.h"
#include <CoreMinimal.h>
#include <UI_ComboBox_Setting.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_ComboBox_Setting : public UUI_ComboBox_Base
{
	GENERATED_BODY()

#pragma region Active

public:
	virtual void ActiveComboBox() override;
	virtual void DeactiveComboBox(FName NameValue, ESelectInfo::Type EnumValue) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setting|Active")
	FLinearColor OutlineColor_Normal;

	UPROPERTY(EditDefaultsOnly, Category = "Setting|Active")
	FLinearColor OutlineColor_Focus;

#pragma endregion

#pragma region Option

public:
	UPROPERTY(EditDefaultsOnly, Category = "Setting|Option")
	EOptionCategory OptionCategory;

#pragma endregion

#pragma region Screen

private:
	void SetOption_Resolution(FName OptionValue);

#pragma endregion

#pragma region Grapic

private:
	void SetOption_Grapic(FName OptionValue);

#pragma endregion

#pragma region System

private:
	void SetOption_Language(FName OptionValue);

#pragma endregion

};