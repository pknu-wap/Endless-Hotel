// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Setting/UI_PopUp_Option.h"
#include "Type/UI/Type_UI_Setting.h"

#pragma region Base

void UUI_PopUp_Option::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	EnumObj = StaticEnum<EOptionValue>();
}

#pragma endregion