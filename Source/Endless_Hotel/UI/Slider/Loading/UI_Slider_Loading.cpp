// Copyright by 2025-2 WAP Game 2 team

#include "UI/Slider/Loading/UI_Slider_Loading.h"

#pragma region Base

void UUI_Slider_Loading::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bStartLoading)
	{
		SetLoadingPercentage(InDeltaTime);
	}
}

#pragma endregion

#pragma region Loading

void UUI_Slider_Loading::SetLoadingPercentage(float InDeltaTime)
{
	LoadingPercentage += InDeltaTime * 0.2f;
	LoadingPercentage = FMath::Clamp(LoadingPercentage, 0, TargetPercentage);
	
	Slide_Slider(LoadingPercentage);
}

#pragma endregion