// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include "Type/UI/Type_UI_Setting.h"
#include "Type/Save/Type_Save.h"
#include <CoreMinimal.h>
#include <Delegates/DelegateCombinations.h>
#include <UI_PopUp_Setting.generated.h>

#pragma region Declare

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSettingHighlight);

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API UUI_PopUp_Setting : public UUI_PopUp_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

#pragma endregion

#pragma region Delegate

public:
	static FSettingHighlight Highlight;

#pragma endregion

#pragma region Highlight

protected:
	UFUNCTION()
	void HighlightButtons();

#pragma endregion

#pragma region Category

public:
	void SetCurrentCategoryText(FText Value);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text_CurrentCategory;

#pragma endregion

#pragma region Option

public:
	void ShowCategoryOption(ESettingCategory Target);
	void SetHideBoxVisibility(ESlateVisibility Option);

protected:
	UFUNCTION()
	void Click_Normal();

	UFUNCTION()
	void Click_Input();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUI_PopUp_Option> UI_Screen;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUI_PopUp_Option> UI_Grapic;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUI_PopUp_Option> UI_Sound;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUI_PopUp_Option> UI_Control_Normal;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUI_PopUp_Option> UI_Control_Input;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUI_PopUp_Option> UI_Gameplay;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUI_PopUp_Option> UI_System;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UBorder> Border_HideBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Normal;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Input;

#pragma endregion

#pragma region Gear

public:
	void StartRotateGear(float Target);

protected:
	void RotateGear(float InDeltaTime);
	const float GetShortestAddAngle(int32 Cur, int32 Tar);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUserWidget> UI_Gear;

	bool bRotateGear = false;

	float CurrentAngle = 0;
	float TargetAngle = 0;

#pragma endregion

#pragma region Save

public:
	FSaveData_Setting Data_Setting;

#pragma endregion

#pragma region Control

protected:
	UFUNCTION()
	void Click_Apply();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Apply;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Cancel;

#pragma endregion

};