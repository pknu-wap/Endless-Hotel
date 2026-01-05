// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/UI_Base.h"
#include <CoreMinimal.h>
#include <UI_Slider_Custom.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UUI_Slider_Custom : public UUI_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Slider

protected:
	UFUNCTION()
	void Slide_Slider(float Value);

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class USlider> Slider_Main;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> ProgressBar_Left;

#pragma endregion

};