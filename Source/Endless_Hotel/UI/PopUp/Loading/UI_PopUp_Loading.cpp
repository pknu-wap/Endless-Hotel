// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Loading/UI_PopUp_Loading.h"
#include "UI/Slider/Loading/UI_Slider_Loading.h"

#pragma region Loading

bool UUI_PopUp_Loading::IsLoadingComplete()
{
	return Slider_Loading->IsLoadingComplete();
}

#pragma endregion