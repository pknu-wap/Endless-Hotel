// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include "Type/UI/Type_UI_Setting.h"
#include <CoreMinimal.h>
#include <UI_PopUp_Setting.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_Setting : public UUI_PopUp_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

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
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUI_Base> UI_Screen;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUI_Base> UI_Grapic;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUI_Base> UI_Sound;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUI_Base> UI_Control;

	/*UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUI_Base> UI_Gameplay;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUI_Base> UI_System;*/

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UBorder> Border_HideBox;

#pragma endregion

#pragma region Gear

public:
	void RotateGear(float TargetAngle);

protected:
	const float GetShortestAddAngle(int32 Cur, int32 Tar);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUserWidget> UI_Gear;

	FTimerHandle AngleHandle;
	float CurrentAngle = 0;

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