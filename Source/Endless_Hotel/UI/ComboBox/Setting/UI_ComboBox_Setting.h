// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/ComboBox/UI_ComboBox_Base.h"
#include <CoreMinimal.h>
#include <UI_ComboBox_Setting.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_ComboBox_Setting : public UUI_ComboBox_Base
{
	GENERATED_BODY()
	
#pragma region Active

protected:
	virtual void ActiveComboBox() override;
	virtual void DeactiveComboBox(FName NameValue, ESelectInfo::Type EnumValue) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Setting|Active")
	FLinearColor OutlineColor_Normal;

	UPROPERTY(EditAnywhere, Category = "Setting|Active")
	FLinearColor OutlineColor_Focus;

#pragma endregion

};