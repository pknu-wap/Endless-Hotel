// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "UI/UI_Base.h"
#include "UI_MainMenu.generated.h"

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_MainMenu : public UUI_Base
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY()
	TObjectPtr<class UUI_Controller> UICon;

#pragma endregion

#pragma region Button

protected:
	UFUNCTION()
	void ButtonClick_Start();

	UFUNCTION()
	void ButtonClick_Dictionary();

	UFUNCTION()
	void ButtonClick_Setting();

	UFUNCTION()
	void ButtonClick_Quit();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Start;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Dictionary;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Setting;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Quit;

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_PopUp_Base> UI_Dictionary;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_PopUp_Base> UI_Setting;

#pragma endregion

};