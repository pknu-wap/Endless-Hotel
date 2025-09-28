// Copyright by 2025-2 WAP Game 2 team

#include "UI/Base/InGame/UI_InGame.h"
#include "Components/Image.h"

#pragma region Crosshair

void UUI_InGame::ChangeCrosshair(bool bCanInteract)
{
	FSlateBrush Brush;

	if (bCanInteract)
	{
		Brush.SetResourceObject(Crosshair_Normal);
	}
	else
	{
		Brush.SetResourceObject(Crosshair_Interact);
	}

	Crosshair->SetBrush(Brush);
}

#pragma endregion