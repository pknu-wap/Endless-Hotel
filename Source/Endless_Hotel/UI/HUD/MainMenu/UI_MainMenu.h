// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/HUD/UI_HUD_Base.h"
#include <CoreMinimal.h>
#include <UI_MainMenu.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_MainMenu : public UUI_HUD_Base
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

#pragma endregion

#pragma region Title

protected:
	void SetTitleImage();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image_Title;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTexture2D> Texture_Clear;

#pragma endregion

#pragma region Button

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UVerticalBox> VBox_Buttons;

	UPROPERTY()
	TArray<TObjectPtr<class UButton>> Buttons;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Compendium;

	const int32 Index_Start = 0;
	const int32 Index_Setting = 1;
	const int32 Index_Quit = 2;

#pragma endregion

#pragma region Click

protected:
	UFUNCTION()
	void Click_Start();

	UFUNCTION()
	void Click_Compendium();

	UFUNCTION()
	void Click_Setting();

	UFUNCTION()
	void Click_Quit();

#pragma endregion

#pragma region Reset

public:
	void ResetOtherButton(const uint8& CurrentIndex);

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_Base> UI_Compendium;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUI_Base> UI_Setting;

#pragma endregion

};