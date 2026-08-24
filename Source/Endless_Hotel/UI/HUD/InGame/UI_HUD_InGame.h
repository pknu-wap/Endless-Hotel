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

#pragma region Active

public:
	virtual void ActiveWidget() override;

#pragma endregion

#pragma region Effect

public:
	void EyeEffectBlur(bool bIsStart, float Value = 1.f);

private:
	void StartInGameHUD(bool bIsStart);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UBackgroundBlur> BackBlur;

	FTimerHandle BlurHandle;
	float CurrentStrength = 0.f;

#pragma endregion

#pragma region Crosshair

private:
	void ShowCrosshair(bool bIsStart);
	void ChangeCrosshair(bool bCanInteract);

private:
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

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image_Brightness;

#pragma endregion

#pragma region SubTitle

public:
	void ShowSubTitle(FText SubTitle, float Delay, float Duration);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image_SubTitle;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text_SubTitle;

#pragma endregion

#pragma region Debug

public:
	void ShowDebugGameInfo(bool bActive);
	void ChangeDebugAnomaly();

private:
	void AddDebugAnomalyRule(EAnomalyRule NewRule);

private:
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