// Copyright by 2025-2 WAP Game 2 team

#include "UI/Controller/UI_Controller.h"
#include "UI/PopUp/UI_PopUp_Base.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/PlayerController.h>

#pragma region Open & Close

UUI_Base* UUI_Controller::OpenWidget(TSubclassOf<UUI_Base> WidgetClass)
{
	UUI_Base* CreatedWidget = CreateWidget<UUI_Base>(GetWorld()->GetFirstPlayerController(), WidgetClass);

	switch (CreatedWidget->WidgetType)
	{
	case EWidgetType::None:
		return CreatedWidget;

	case EWidgetType::HUD:
		ClearAllWidget();
		break;

	case EWidgetType::PopUp_Pause:
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		break;
	}

	CreatedWidget->AddToViewport(Widget_ZOrder);
	PopUpWidgets.Add(CreatedWidget);

	AdjustZOrder(true);
	SetInputMode(CreatedWidget->InputModeType);

	return CreatedWidget;
}

void UUI_Controller::CloseWidget()
{
	if (PopUpWidgets.IsEmpty())
	{
		return;
	}

	switch (PopUpWidgets.Top()->WidgetType)
	{
	case EWidgetType::None:
	case EWidgetType::HUD:
		return;

	case EWidgetType::PopUp_Pause:
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		break;
	}

	AdjustZOrder(false);

	PopUpWidgets.Top()->RemoveFromViewport();
	PopUpWidgets.Pop();

	SetInputMode(PopUpWidgets.Top()->InputModeType);
}

void UUI_Controller::ClearAllWidget()
{
	for (auto Target : PopUpWidgets)
	{
		Target->RemoveFromViewport();
	}

	PopUpWidgets.Empty();
	Widget_ZOrder = 0;
}

#pragma endregion

#pragma region Input

void UUI_Controller::SetInputMode(const EInputModeType& InputMode)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	switch (InputMode)
	{
	case EInputModeType::GameOnly:
	{
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
		break;
	}
	case EInputModeType::UIOnly:
	{
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(PopUpWidgets.Top()->TakeWidget());
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
		break;
	}
	case EInputModeType::GameAndUI:
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(PopUpWidgets.Top()->TakeWidget());
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
		break;
	}
	}
}

#pragma endregion

#pragma region ZOrder

void UUI_Controller::AdjustZOrder(bool bUp)
{
	int32 Value = bUp ? 1 : -1;
	Widget_ZOrder = FMath::Clamp(Widget_ZOrder + Value, Min_ZOrder, Max_ZOrder);
}

#pragma endregion