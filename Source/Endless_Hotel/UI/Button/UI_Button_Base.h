// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/UI_Base.h"
#include <Components/Button.h>
#include <CoreMinimal.h>
#include <UI_Button_Base.generated.h>

UCLASS(Abstract, Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Button_Base : public UUI_Base
{
	GENERATED_BODY()

#pragma region Button

public:
	UButton* GetButton() { return Button; }

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button;

#pragma endregion

};