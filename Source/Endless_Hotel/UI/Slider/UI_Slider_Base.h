// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>
#include <UI_Slider_Base.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Slider_Base : public UUserWidget
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Owner

private:
	void SetWidgetOwner();

protected:
	UPROPERTY()
	TWeakObjectPtr<class UUI_Base> Owner;

#pragma endregion

#pragma region Slider

public:
	class USlider* GetSlider() { return Slider_Default; }

protected:
	UFUNCTION()
	virtual void Slide_Slider(float Value);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class USlider> Slider_Default;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> ProgressBar_Left;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text_Value;

#pragma endregion

};