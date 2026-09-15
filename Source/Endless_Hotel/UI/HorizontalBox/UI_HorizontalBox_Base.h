// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "UI/UI_Base.h"
#include <Components/HorizontalBox.h>
#include <Components/HorizontalBoxSlot.h>
#include <CoreMinimal.h>
#include <UI_HorizontalBox_Base.generated.h>

UCLASS(Abstract, Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_HorizontalBox_Base : public UUI_Base
{
	GENERATED_BODY()
	
#pragma region HorizontalBox

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UHorizontalBox> HorizontalBox;

#pragma endregion

};