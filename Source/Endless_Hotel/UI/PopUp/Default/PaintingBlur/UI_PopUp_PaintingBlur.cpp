// Copyright by 2025-2 WAP Game 2 team


#include "UI/PopUp/Default/PaintingBlur/UI_PopUp_PaintingBlur.h"
#include "Components/BackgroundBlur.h"

#pragma region Blur

void UUI_PopUp_PaintingBlur::StartPaintingBlur()
{
	const float TargetStrength = 20.f;

	BackBlur->SetBlurStrength(TargetStrength);
}

#pragma endregion