// Copyright by 2025-2 WAP Game 2 team

#include "UI/Controller/UI_Controller.h"
#include "UI/PopUp/UI_PopUp_Base.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/PlayerController.h>

#pragma region Base

UUI_Controller::UUI_Controller()
{
	static ConstructorHelpers::FClassFinder<UUI_Base> MainMenuFinder(TEXT("/Game/EndlessHotel/UI/Blueprint/MainMenu/WBP_MainMenu.WBP_MainMenu_C"));
	if (MainMenuFinder.Succeeded())
	{
		UI_MainMenu = MainMenuFinder.Class;
	}

	static ConstructorHelpers::FClassFinder<UUI_Base> InGameFinder(TEXT("/Game/EndlessHotel/UI/Blueprint/InGame/WBP_InGame.WBP_InGame_C"));
	if (InGameFinder.Succeeded())
	{
		UI_InGame = InGameFinder.Class;
	}
}

#pragma endregion

#pragma region Open & Close

UUI_Base* UUI_Controller::OpenWidget(TSubclassOf<UUI_Base> WidgetClass)
{
	UUI_Base* CreatedWidget = CreateWidget<UUI_Base>(GetWorld(), WidgetClass);

	switch (CreatedWidget->WidgetType)
	{
	case EWidgetType::PopUp_Pause:
		UGameplayStatics::SetGamePaused(GetWorld(), true);

	case EWidgetType::HUD:
	case EWidgetType::PopUp:
		CreatedWidget->AddToViewport(Widget_ZOrder);
		PopUpWidgets.Add(CreatedWidget);
		break;
	}

	AdjustZOrder(true);
	SetInputMode(CreatedWidget->InputModeType);

	return CreatedWidget;
}

void UUI_Controller::CloseWidget()
{
	switch (PopUpWidgets.Top()->WidgetType)
	{
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
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

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

#pragma region Adjust

void UUI_Controller::AdjustZOrder(bool bUp)
{
	if (bUp)
	{
		Widget_ZOrder = FMath::Clamp(Widget_ZOrder + 1, Min_ZOrder, Max_ZOrder);
		return;
	}

	Widget_ZOrder = FMath::Clamp(Widget_ZOrder - 1, Min_ZOrder, Max_ZOrder);
}

#pragma endregion

#pragma region Widget

void UUI_Controller::OpenMapBaseWidget()
{
	ClearAllWidget();

	switch (UEHGameInstance::CurrentMap)
	{
	case EMapType::MainMenu:
		OpenWidget(UI_MainMenu);
		break;

	case EMapType::Hotel:
		OpenWidget(UI_InGame);
		break;
	}
}

#pragma endregion