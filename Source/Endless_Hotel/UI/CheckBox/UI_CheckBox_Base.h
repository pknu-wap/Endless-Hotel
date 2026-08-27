// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/UI_Base.h"
#include <Components/CheckBox.h>
#include <CoreMinimal.h>
#include <UI_CheckBox_Base.generated.h>

UCLASS(Abstract, Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_CheckBox_Base : public UUI_Base
{
	GENERATED_BODY()
	
#pragma region CheckBox

public:
	UCheckBox* GetCheckBox() { return CheckBox; }

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCheckBox> CheckBox;

#pragma endregion

};