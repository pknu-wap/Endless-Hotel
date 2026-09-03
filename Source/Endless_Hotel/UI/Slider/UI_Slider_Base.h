// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/UI_Base.h"
#include <Components/Slider.h>
#include <CoreMinimal.h>
#include <UI_Slider_Base.generated.h>

UCLASS(Abstract, Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Slider_Base : public UUI_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Slider

public:
	USlider* GetSlider() { return Slider; }

protected:
	UFUNCTION()
	virtual void Slide_Slider(float Value);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USlider> Slider;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> ProgressBar;

#pragma endregion

};