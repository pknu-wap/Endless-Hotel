// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUp/Default/UI_PopUp_Default.h"
#include "Delegates/DelegateCombinations.h"
#include "UI_PopUp_Setting.generated.h"

#pragma region Declare

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSettingGrapic, int32, Value, int32, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSettingLanguage, FString, Value, int32, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSettingResolution, FIntPoint, Value, int32, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSettingScreen, EWindowMode::Type, Value, int32, Index);

#pragma endregion

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_Setting : public UUI_PopUp_Default
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

#pragma endregion

#pragma region Setting

protected:
	UPROPERTY()
	TObjectPtr<class UGameUserSettings> SettingHandle;

	int32 Value_Grapic;
	FString Value_Language;
	FIntPoint Value_Resolution;
	EWindowMode::Type Value_Screen;
	float Value_Sound;

#pragma endregion

#pragma region Delegate

public:
	static FSettingGrapic SettingGrapic;
	static FSettingLanguage SettingLanguage;
	static FSettingResolution SettingResolution;
	static FSettingScreen SettingScreen;

#pragma endregion

#pragma region Buttons

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UHorizontalBox> Buttons_Grapic;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UHorizontalBox> Buttons_Language;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UHorizontalBox> Buttons_Resolution;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UHorizontalBox> Buttons_Screen;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USoundClass> SoundMaster;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class USlider> Slider_Sound;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Cancel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Apply;

#pragma endregion

#pragma region Click

protected:
	UFUNCTION()
	void ButtonClick_Grapic(int32 Value, int32 Index);

	UFUNCTION()
	void ButtonClick_Language(FString Value, int32 Index);

	UFUNCTION()
	void ButtonClick_Resolution(FIntPoint Value, int32 Index);

	UFUNCTION()
	void ButtonClick_Screen(EWindowMode::Type Value, int32 Index);

	UFUNCTION()
	void SliderClick_Sound(float Value);

	UFUNCTION()
	void ButtonClick_Apply();

#pragma endregion

};