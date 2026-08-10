// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include "Type/UI/Type_Setting.h"
#include "Type/Save/Type_Save.h"
#include "Type/Level/Type_Level.h"
#include <CoreMinimal.h>
#include <Delegates/DelegateCombinations.h>
#include <UI_PopUp_Setting.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UUI_PopUp_Setting : public UUI_PopUp_Base
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

#pragma endregion

#pragma region Show & Hide

public:
	virtual void ShowWidget() override;
	virtual void HideWidget() override;

#pragma endregion

#pragma region Delegate

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSettingHighlight);
	static FSettingHighlight Highlight;

#pragma endregion

#pragma region Highlight

private:
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

private:
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
	TObjectPtr<class UBorder> Border_HideBox2;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Normal;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Input;

#pragma endregion

#pragma region Gear

public:
	void StartRotateGear(float Target);

private:
	void FindGearActor();
	void RotateGear(float InDeltaTime);
	const int32 GetShortestAdditionAngle(int32 Cur, int32 Tar);
	void TurnOnGearLight(bool bOn);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> UI_Gear;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> SW_Gear;

private:
	UPROPERTY()
	TWeakObjectPtr<class AStaticMeshActor> SM_Gear;

	UPROPERTY()
	TWeakObjectPtr<class USpotLightComponent> Comp_SpotLight;

	UPROPERTY()
	TWeakObjectPtr<class UExponentialHeightFogComponent> Comp_Fog;

	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC_Gear;

private:
	// UI
	float CurrentAngle = 0.f;
	float FinalAngle = 0.f;
	const float RotateSpeed = 45.f;

private:
	// Actor
	FRotator OriginRot;
	FQuat CurrentQuat;
	FQuat FinalQuat;

private:
	FTimerHandle LightHandle;

private:
	bool bRotateGear = false;

#pragma endregion

#pragma region Save

public:
	FSaveData_Setting Data_Setting;

#pragma endregion

#pragma region Control

private:
	UFUNCTION()
	void Click_Apply();

	virtual FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	void AdjustCategoryIndex(bool bUp);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Apply;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Cancel;

private:
	UPROPERTY()
	TArray<TObjectPtr<class UUI_Button_Setting>> CategoryButtons;

	int8 CategoryIndex = 0;

#pragma endregion

};