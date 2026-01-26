// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include <CoreMinimal.h>
#include <UI_PopUp_Option.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_Option : public UUI_PopUp_Base
{
	GENERATED_BODY()
	
#pragma region Input

public:
	virtual void Input_ESC() override {}

#pragma endregion

};