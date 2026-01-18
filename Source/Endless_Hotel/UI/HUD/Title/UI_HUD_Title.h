// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/HUD/UI_HUD_Base.h"
#include "Type/UI/Type_UI_Title.h"
#include <CoreMinimal.h>
#include <UI_HUD_Title.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_HUD_Title : public UUI_HUD_Base
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

#pragma endregion

#pragma region Click

protected:
	UFUNCTION()
	void Click_Start();

	UFUNCTION()
	void Click_Setting();

	UFUNCTION()
	void Click_Quit();

#pragma endregion

#pragma region Hover

public:
	void PlayButtonAnim_Hover(ETitleButtonType ButtonType);
	void PlayButtonAnim_Unhover(ETitleButtonType ButtonType);

protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> Anim_Hover_Start;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> Anim_Hover_Setting;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> Anim_Hover_Quit;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> Anim_Unhover_Start;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> Anim_Unhover_Setting;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> Anim_Unhover_Quit;

#pragma endregion

#pragma region Button

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Start;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Setting;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Quit;

#pragma endregion

#pragma region Logo

protected:
	void SetLogoImage();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image_Logo;

	UPROPERTY(EditAnywhere, Category = "Logo")
	TObjectPtr<class UTexture2D> Texture_Clear;

#pragma endregion

#pragma region Setting

protected:
	UPROPERTY(EditAnywhere, Category = "Setting")
	TSubclassOf<class UUI_Base> UI_Setting;

#pragma endregion

};