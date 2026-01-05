// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include "Type/UI/Type_UI.h"
#include "Type/Save/Type_Save.h"
#include <CoreMinimal.h>
#include <Delegates/DelegateCombinations.h>
#include <UI_PopUp_Setting.generated.h>

#pragma region Declare

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSettingGrapic,		 FButtonInfo, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSettingResolution,	 FButtonInfo, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSettingFrame,		 FButtonInfo, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSettingScreen,		 FButtonInfo, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSettingSensitivity, float,		  Value);

#pragma endregion

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_Setting : public UUI_PopUp_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

#pragma endregion

#pragma region Data

protected:
	void LoadSettingData();

protected:
	FSettingSaveData SettingData;

#pragma endregion

#pragma region Setting

protected:
	void SettingButtonOwner(class UHorizontalBox* ButtonBox);

protected:
	UPROPERTY()
	TObjectPtr<class UGameUserSettings> SettingHandle;

#pragma endregion

#pragma region Delegate

public:
	static FSettingGrapic SettingGrapic;
	static FSettingResolution SettingResolution;
	static FSettingFrame SettingFrame;
	static FSettingScreen SettingScreen;
	static FSettingSensitivity SettingSensitivity;

#pragma endregion

#pragma region Button

protected:
	UFUNCTION()
	void Click_Grapic(FButtonInfo Value);

	UFUNCTION()
	void Click_Resolution(FButtonInfo Value);

	UFUNCTION()
	void Click_Frame(FButtonInfo Value);

	UFUNCTION()
	void Click_Screen(FButtonInfo Value);

	UFUNCTION()
	void Slide_Sound(float Value);

	UFUNCTION()
	void Slide_Sensitivity(float Value);

protected:
	UFUNCTION()
	void Click_Apply();

protected:
	UFUNCTION()
	void Click_Reset();

	UFUNCTION()
	void Click_Language();

	UFUNCTION()
	void Click_Brightness();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UHorizontalBox> Buttons_Grapic;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UHorizontalBox> Buttons_Resolution;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UHorizontalBox> Buttons_Frame;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UHorizontalBox> Buttons_Screen;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUI_Slider_Custom> Slider_Sound;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USoundClass> SoundMaster;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUI_Slider_Custom> Slider_Sensitivity;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Cancel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Apply;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Reset;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Language;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Brightness;

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_Base> UI_Reset;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_Base> UI_Language;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_Base> UI_Brightness;

#pragma endregion

};