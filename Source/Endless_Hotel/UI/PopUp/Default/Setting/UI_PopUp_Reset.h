// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUp/Default/UI_PopUp_Default.h"
#include "UI_PopUp_Reset.generated.h"

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_Reset : public UUI_PopUp_Default
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Button

protected:
	UFUNCTION()
	void ButtonClick_Yes();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Yes;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_No;

#pragma endregion

};