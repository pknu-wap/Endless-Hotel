// Copyright by 2025-2 WAP Game 2 team

#include "UI_PaintingBlur.h"
#include <Blueprint/UserWidget.h>
#include <Components/BackgroundBlur.h>

#pragma region Blur

void UUI_PaintingBlur::StartPaintingBlur()
{
	const float TargetStrength = 20.f;

	BackBlur->SetBlurStrength(TargetStrength);
}

#pragma endregion