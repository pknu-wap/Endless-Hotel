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

#pragma endregion

#pragma region Button

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UVerticalBox> VBox_Buttons;

	UPROPERTY()
	TArray<TObjectPtr<class UButton>> Buttons;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Compendium;

	const int32 Index_Start = 0;
	const int32 Index_Setting = 1;
	const int32 Index_Quit = 2;

#pragma endregion

#pragma region Click

protected:
	UFUNCTION()
	void ButtonClick_Start();

	UFUNCTION()
	void ButtonClick_Compendium();

	UFUNCTION()
	void ButtonClick_Setting();

	UFUNCTION()
	void ButtonClick_Quit();

#pragma endregion

#pragma region Reset

public:
	void ResetOtherButton(const uint8& CurrentIndex);

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_PopUp_Base> UI_Compendium;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_PopUp_Base> UI_Setting;

#pragma endregion

};