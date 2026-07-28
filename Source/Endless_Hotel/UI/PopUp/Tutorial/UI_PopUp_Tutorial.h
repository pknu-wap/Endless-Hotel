// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include <CoreMinimal.h>
#include <UI_PopUp_Tutorial.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_Tutorial : public UUI_PopUp_Base
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Show

protected:
	virtual void ShowWidget() override;

#pragma endregion

#pragma region Input

protected:
	virtual void Input_ESC() override;

private:
	void CloseTutorial();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_ESC;

#pragma endregion

#pragma region Animation

protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> WidgetAnim_Disappear;

#pragma endregion

};