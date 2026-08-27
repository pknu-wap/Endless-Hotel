// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "UI/HorizontalBox/UI_HorizontalBox_Base.h"
#include "Interface/UI/OptionInterface.h"
#include <CoreMinimal.h>
#include <UI_HorizontalBox_Setting.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_HorizontalBox_Setting : public UUI_HorizontalBox_Base, public IOptionInterface
{
	GENERATED_BODY()
	
#pragma region Interface

public:
	virtual void InitOption(EOptionCategory Category, TArray<FOptionValuePair> Values) override;

#pragma endregion

#pragma region Highlight

public:
	void Highlight(EOptionValue TargetValue);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Highlight")
	FLinearColor Color_Highlight;

	UPROPERTY(EditDefaultsOnly, Category = "Highlight")
	FLinearColor Color_Default;

#pragma endregion

#pragma region Button

private:
	UPROPERTY(EditDefaultsOnly, Category = "Button")
	TSubclassOf<class UUI_Button_Option> ButtonClass;

	UPROPERTY()
	TArray<TObjectPtr<class UUI_Button_Option>> Buttons;

#pragma endregion

};