// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "UI/UI_Base.h"
#include "UI_PopUp_Base.generated.h"

UCLASS(Abstract, Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_Base : public UUI_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

#pragma endregion

#pragma region Input

protected:
	virtual void Input_Enter() PURE_VIRTUAL(UUI_PopUp_Base::Input_Enter, );
	virtual void Input_ESC();

#pragma endregion

};