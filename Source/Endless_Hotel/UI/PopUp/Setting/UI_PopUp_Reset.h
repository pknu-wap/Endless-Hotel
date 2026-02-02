// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include "Type/UI/Type_UI_Setting.h"
#include <CoreMinimal.h>
#include <UI_PopUp_Reset.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_Reset : public UUI_PopUp_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Category

protected:
	UPROPERTY(EditAnywhere, Category = "Setting|Category")
	EOptionCategory OptionCategory;

#pragma endregion

#pragma region Click

protected:
	UFUNCTION()
	void Click_Yes();

#pragma endregion

#pragma region Button

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Yes;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_No;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_ESC;

#pragma endregion

};