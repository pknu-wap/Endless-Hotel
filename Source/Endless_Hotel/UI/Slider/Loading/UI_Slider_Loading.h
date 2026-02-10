// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/Slider/UI_Slider_Base.h"
#include <CoreMinimal.h>
#include <UI_Slider_Loading.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UUI_Slider_Loading : public UUI_Slider_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

#pragma endregion

#pragma region Loading

protected:
	void SetLoadingPercentage();

#pragma endregion

};