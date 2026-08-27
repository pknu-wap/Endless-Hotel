// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/Slider/UI_Slider_Base.h"
#include "Interface/UI/OptionInterface.h"
#include <CoreMinimal.h>
#include <UI_Slider_Setting.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Slider_Setting : public UUI_Slider_Base, public IOptionInterface
{
	GENERATED_BODY()

#pragma region Interface

public:
	virtual void InitOption(EOptionCategory Category, TArray<FOptionValuePair> Values) override;

#pragma endregion

#pragma region Slider

protected:
	virtual void Slide_Slider(float Value) override;

#pragma endregion

#pragma region Option

private:
	EOptionCategory OptionCategory = EOptionCategory::None;

#pragma endregion

#pragma region TextBlock

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextBlock;

#pragma endregion

};