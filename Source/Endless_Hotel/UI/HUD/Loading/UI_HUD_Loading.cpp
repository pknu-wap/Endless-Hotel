// Copyright by 2025-2 WAP Game 2 team

#include "UI/HUD/Loading/UI_HUD_Loading.h"
#include "UI/Slider/Loading/UI_Slider_Loading.h"

#pragma region Show

void UUI_HUD_Loading::ShowWidget()
{
	Super::ShowWidget();
	
	Slider_Loading->ResetLoadingPercentage();
}

#pragma endregion

#pragma region Loading

bool UUI_HUD_Loading::IsLoadingCompleted()
{
	return Slider_Loading->IsLoadingCompleted();
}

#pragma endregion