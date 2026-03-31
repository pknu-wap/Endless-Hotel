// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include <CoreMinimal.h>
#include <UI_PopUp_Loading.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_Loading : public UUI_PopUp_Base
{
	GENERATED_BODY()

#pragma region Input

protected:
	virtual void Input_ESC() override {}

#pragma endregion

};