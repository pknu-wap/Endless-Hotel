// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include <CoreMinimal.h>
#include <UI_PopUp_WrongCheck.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UUI_PopUp_WrongCheck : public UUI_PopUp_Base
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Button

private:
	UFUNCTION()
	void Click_Yes();

	UFUNCTION()
	void Click_No();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Yes;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_No;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_ESC;

#pragma endregion

};