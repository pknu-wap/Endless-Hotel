// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUp/Default/UI_PopUp_Default.h"
#include "UI_PopUp_Brightness.generated.h"

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_Brightness : public UUI_PopUp_Default
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

#pragma endregion

#pragma region Data

protected:
	FSettingSaveData SettingData;

#pragma endregion

#pragma region Button

protected:
	UFUNCTION()
	void ButtonClick_Apply();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Apply;

#pragma endregion

#pragma region Brighness

protected:
	UFUNCTION()
	void Slide_Brightness(float Value);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class USlider> Slider_Brightness;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image_Brightness;

	float Value_Brightness = 0.5f;

#pragma endregion

};