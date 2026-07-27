// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/HUD/UI_HUD_Base.h"
#include "Type/Anomaly/Type_AnomalyID.h"
#include "Type/Anomaly/Type_AnomalyRule.h"
#include <CoreMinimal.h>
#include <UI_HUD_InGame.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_HUD_InGame : public UUI_HUD_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Show

public:
	virtual void ShowWidget() override;

	void StartInGameHUD(bool bIsStart);

#pragma endregion

#pragma region Crosshair

private:
	void ShowCrosshair(bool bIsStart);

	UFUNCTION()
	void ChangeCrosshair(bool bCanInteract);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image_Crosshair_Center;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> WidgetAnim_ShowCrosshair;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> WidgetAnim_Interact;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> WidgetAnim_Normal;

private:
	bool bIsCrosshairInteractMode = false;

#pragma endregion

#pragma region Brightness

public:
	void SetBrightness(float Value);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image_Brightness;

#pragma endregion

#pragma region Blur

public:
	void EyeEffectBlur(bool bIsStart, float Value = 1.f);
	void RemoveEyeEffectBlur();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UBackgroundBlur> BackBlur;

	FTimerHandle BlurHandle;
	float CurrentStrength = 0.f;

#pragma endregion

#pragma region Demo

protected:
	UFUNCTION()
	void OpenDemoWidget();

#pragma endregion

#pragma region SubTitle

public:
	void ShowSubTitle(FText SubTitle, float Delay, float Duration);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image_SubTitle;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text_SubTitle;

#pragma endregion

#pragma region Debug

public:
	void ShowDebugGameInfo(bool bActive);

private:
	UFUNCTION()
	void AddDebugAnomalyRule(EAnomalyRule NewRule);

	UFUNCTION()
	void ChangeDebugAnomaly();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text_Rule;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UVerticalBox> VB_Rule;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text_Current;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text_Next;

#pragma endregion

};