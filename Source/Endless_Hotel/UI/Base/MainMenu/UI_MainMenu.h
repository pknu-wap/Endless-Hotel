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

#pragma region Buttons

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
	TObjectPtr<class UButton> StartButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> DictionaryButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> SettingButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> QuitButton;

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_PopUp_Base> UI_Dictionary;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_PopUp_Base> UI_Setting;

#pragma endregion

};