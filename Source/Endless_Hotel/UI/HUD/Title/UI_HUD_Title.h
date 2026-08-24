// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/HUD/UI_HUD_Base.h"
#include "Type/UI/Type_Title.h"
#include <CoreMinimal.h>
#include <UI_HUD_Title.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_HUD_Title : public UUI_HUD_Base
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

#pragma region Show

public:
	virtual void ShowWidget() override;

#pragma endregion

#pragma region Click

private:
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

private:
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

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Start;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Setting;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Quit;

#pragma endregion

#pragma region Logo

private:
	void SetLogoImage();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image_Logo;

	UPROPERTY(EditAnywhere, Category = "Logo")
	TObjectPtr<class UTexture2D> Texture_NoClear;

	UPROPERTY(EditAnywhere, Category = "Logo")
	TObjectPtr<class UTexture2D> Texture_Clear;

#pragma endregion

#pragma region BGM

public:
	void StopBGM(float Duration);

private:
	UFUNCTION()
	void PlayBGM();

private:
	UPROPERTY(Transient)
	TObjectPtr<class UAudioComponent> AC;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> SW_BGM;

#pragma endregion

};