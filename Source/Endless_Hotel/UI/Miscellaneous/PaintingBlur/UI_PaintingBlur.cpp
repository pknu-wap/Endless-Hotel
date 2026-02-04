// Copyright by 2025-2 WAP Game 2 team

#include "UI/Miscellaneous/PaintingBlur/UI_PaintingBlur.h"
#include <Components/BackgroundBlur.h>

#pragma region Blur

void UUI_PaintingBlur::StartPaintingBlur()
{
	const float TargetStrength = 20.f;

	BackBlur->SetBlurStrength(TargetStrength);
}

#pragma endregion