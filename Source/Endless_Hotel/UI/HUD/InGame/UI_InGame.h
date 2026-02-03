// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/HUD/UI_HUD_Base.h"
#include <CoreMinimal.h>
#include <UI_InGame.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_InGame : public UUI_HUD_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Crosshair

protected:
	UFUNCTION()
	void ChangeCrosshair(bool bCanInteract);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image_Crosshair_Center;

protected:
	UFUNCTION()
	void ShowCrosshair(bool bIsShow);

protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> WidgetAnim_ShowCrosshair;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> WidgetAnim_Interact;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> WidgetAnim_Normal;

	bool bIsCrosshairInteractMode = false;

#pragma endregion

#pragma region Brightness

public:
	void SetBrightness(float Value);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image_Brightness;

#pragma endregion

#pragma region Demo

protected:
	UFUNCTION()
	void OpenDemoWidget();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_Base> UI_Demo;

#pragma endregion

};