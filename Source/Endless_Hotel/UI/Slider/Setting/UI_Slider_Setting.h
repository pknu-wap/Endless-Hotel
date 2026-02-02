// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/Slider/UI_Slider_Base.h"
#include "Type/UI/Type_UI_Setting.h"
#include <CoreMinimal.h>
#include <UI_Slider_Setting.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Slider_Setting : public UUI_Slider_Base
{
	GENERATED_BODY()
	
#pragma region Category

public:
	UPROPERTY(EditAnywhere, Category = "Setting|Category")
	EOptionCategory OptionCategory;

#pragma endregion

#pragma region Slider

public:
	virtual void Slide_Slider(float Value) override;

#pragma endregion

#pragma region Sound

protected:
	UPROPERTY(EditAnywhere, Category = "Setting|Sound")
	TObjectPtr<class USoundClass> SC_Target;

#pragma endregion

};