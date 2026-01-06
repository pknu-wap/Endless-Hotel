// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include <CoreMinimal.h>
#include <UI_PopUp_Escape.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_Escape : public UUI_PopUp_Base
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Button

protected:
	UFUNCTION()
	void Click_Setting();

	UFUNCTION()
	void Click_MainMenu();

	UFUNCTION()
	void Click_Quit();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Resume;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Setting;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_MainMenu;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Quit;

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_Base> UI_Setting;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_Base> UI_QuitCheck;

#pragma endregion

};