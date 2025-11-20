// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUp/Default/UI_PopUp_Default.h"
#include "Delegates/DelegateCombinations.h"
#include "UI_PopUp_Setting.generated.h"

#pragma region Declare

struct FButtonInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSettingGrapic,		FButtonInfo, Value, int32, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSettingResolution,	FButtonInfo, Value, int32, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSettingFrame,			FButtonInfo, Value, int32, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSettingScreen,		FButtonInfo, Value, int32, Index);

// 해당 기능은 최종 이후에 추가 예정
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSettingLanguage,		FButtonInfo, Value, int32, Index);

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
	void SettingButtonOwner(class UHorizontalBox* ButtonBox);

protected:
	UPROPERTY()
	TObjectPtr<class UGameUserSettings> SettingHandle;

	int32 Value_Grapic;
	FIntPoint Value_Resolution;
	float Value_Frame;
	EWindowMode::Type Value_Screen;
	float Value_Sound;

	// 해당 기능은 최종 이후에 추가 예정
	//float Value_Brightness;
	//FString Value_Language;

#pragma endregion

#pragma region Delegate

public:
	static FSettingGrapic SettingGrapic;
	static FSettingResolution SettingResolution;
	static FSettingFrame SettingFrame;
	static FSettingScreen SettingScreen;

	// 해당 기능은 최종 이후에 추가 예정
	//static FSettingLanguage SettingLanguage;

#pragma endregion

#pragma region Button

protected:
	UFUNCTION()
	void ButtonClick_Grapic(FButtonInfo Value, int32 Index);

	UFUNCTION()
	void ButtonClick_Resolution(FButtonInfo Value, int32 Index);

	UFUNCTION()
	void ButtonClick_Frame(FButtonInfo Value, int32 Index);

	UFUNCTION()
	void ButtonClick_Screen(FButtonInfo Value, int32 Index);

	UFUNCTION()
	void SliderClick_Sound(FButtonInfo Value);

	// 해당 기능은 최종 이후에 추가 예정
	/*UFUNCTION()
	void SliderClick_Brightness(FButtonInfo Value);

	UFUNCTION()
	void ButtonClick_Language(FButtonInfo Value, int32 Index);*/

	UFUNCTION()
	void ButtonClick_Apply();

	UFUNCTION()
	void ButtonClick_Reset();

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
	TObjectPtr<class USlider> Slider_Sound;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USoundClass> SoundMaster;

	// 해당 기능은 최종 이후에 추가 예정
	/*UPROPERTY(meta = (BindWidget))
	TObjectPtr<class USlider> Slider_Brightness;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Language;*/

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Cancel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Apply;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Reset;

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_PopUp_Base> UI_Reset;

	// 해당 기능은 최종 이후 추가 예정
	/*UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_PopUp_Base> UI_Language;*/

#pragma endregion

#pragma region Hightlight

public:
	void HighlightButton(const enum ESettingCategory& ButtonType, const uint8& TargetIndex);

#pragma endregion

};