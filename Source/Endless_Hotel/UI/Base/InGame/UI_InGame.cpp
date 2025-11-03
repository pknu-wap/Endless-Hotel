// Copyright by 2025-2 WAP Game 2 team

#include "UI/Base/InGame/UI_InGame.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"

#pragma region Base

void UUI_InGame::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CanInteract.AddDynamic(this, &ThisClass::ChangeCrosshair);
}

#pragma endregion

#pragma region Crosshair

FCanInteract UUI_InGame::CanInteract;

void UUI_InGame::ChangeCrosshair(bool bCanInteract)
{
	UCanvasPanelSlot* CPSlot = Cast<UCanvasPanelSlot>(Crosshair->Slot);

	FSlateBrush Brush;

	if (bCanInteract)
	{
		Brush.SetResourceObject(Crosshair_Normal);
		Brush.TintColor = FSlateColor(FColor(1, 1, 1, 1));
		CPSlot->SetSize(FVector2D(14, 14));
		CPSlot->SetPosition(FVector2D(-7, -7));
	}
	else
	{
		Brush.SetResourceObject(Crosshair_Interact);
		Brush.TintColor = FSlateColor(FColor(1, 1, 1, 0.3f));
		CPSlot->SetSize(FVector2D(24, 24));
		CPSlot->SetPosition(FVector2D(-12, -12));
	}

	Crosshair->SetBrush(Brush);
}

#pragma endregion