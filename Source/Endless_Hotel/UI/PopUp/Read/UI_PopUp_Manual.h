// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "UI/PopUp/Read/UI_PopUp_Read.h"
#include <CoreMinimal.h>
#include <UI_PopUp_Manual.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_Manual : public UUI_PopUp_Read
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Click

private:
	UFUNCTION()
	void Click_ButtonNext();

#pragma endregion

#pragma region Button

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Next;

#pragma endregion

#pragma region Animation

private:
	UFUNCTION()
	void PlayArrowAnimation();

	UFUNCTION()
	void StopArrowAnimation();

private:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> WidgetAnim_Arrow;

#pragma endregion

};