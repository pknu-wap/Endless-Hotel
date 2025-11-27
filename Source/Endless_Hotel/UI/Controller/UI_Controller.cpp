// Copyright by 2025-2 WAP Game 2 team

#include "UI/Controller/UI_Controller.h"
#include "UI/PopUp/UI_PopUp_Base.h"
#include "GameFramework/PlayerController.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "Kismet/GameplayStatics.h"

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

UUI_Base* UUI_Controller::OpenWidget(TSubclassOf<UUI_Base> WidgetClass, const EWidgetType& WidgetType, const EInputModeType& InputMode)
{
	FPopUpWidget PopUpWidget;
	PopUpWidget.WidgetType = WidgetType;
	PopUpWidget.InputModeType = InputMode;
	PopUpWidget.PopUpWidget = CreateWidget<UUI_Base>(GetWorld(), WidgetClass);

	if (!PopUpWidgets.IsEmpty())
	{
		AdjustZOrder(true);
	}

	switch (WidgetType)
	{
	case EWidgetType::Base:
	{
		if (!PopUpWidgets.IsEmpty())
		{
			PopUpWidgets[0] = PopUpWidget;
		}
		else
		{
			PopUpWidgets.Add(PopUpWidget);
		}
		PopUpWidget.PopUpWidget->AddToViewport(Widget_ZOrder);
		break;
	}
	case EWidgetType::PopUp:
	{
		PopUpWidget.PopUpWidget->AddToViewport(Widget_ZOrder);
		PopUpWidgets.Add(PopUpWidget);
		break;
	}
	case EWidgetType::PopUpStrong:
	{
		GEngine->GameViewport->AddViewportWidgetContent(PopUpWidget.PopUpWidget->TakeWidget(), Widget_ZOrder);
		PopUpWidgets.Add(PopUpWidget);
		break;
	}
	}

	SetInputMode(PopUpWidget.InputModeType);

	return PopUpWidget.PopUpWidget;
}

void UUI_Controller::CloseWidget()
{
	if (PopUpWidgets.IsEmpty())
	{
		return;
	}

	FPopUpWidget PopUpWidget = PopUpWidgets[Widget_ZOrder];
	PopUpWidgets.RemoveAt(Widget_ZOrder);

	if (!PopUpWidgets.IsEmpty())
	{
		AdjustZOrder(false);
	}

	SetInputMode(PopUpWidgets[Widget_ZOrder].InputModeType);

	switch (PopUpWidget.WidgetType)
	{
	default:
		PopUpWidget.PopUpWidget->RemoveFromViewport();
		break;

	case EWidgetType::PopUpStrong:
		GEngine->GameViewport->RemoveViewportWidgetContent(PopUpWidget.PopUpWidget->TakeWidget());
		break;
	}
}

void UUI_Controller::ClearAllPopUpWidget()
{
	for (int32 Index = 0; Index < PopUpWidgets.Num(); Index++)
	{
		if (PopUpWidgets[Index].WidgetType != EWidgetType::PopUpStrong)
		{
			PopUpWidgets.RemoveAt(Index);
		}
	}

	Widget_ZOrder = PopUpWidgets.Num() - 1;
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
		InputMode.SetWidgetToFocus(PopUpWidgets[Widget_ZOrder].PopUpWidget->TakeWidget());
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
		break;
	}
	case EInputModeType::GameAndUI:
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(PopUpWidgets[Widget_ZOrder].PopUpWidget->TakeWidget());
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
	constexpr int32 Max_ZOrder = 100;
	constexpr int32 Min_ZOrder = 0;

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
	Widget_ZOrder = 0;

	switch (UEHGameInstance::CurrentMap)
	{
	case EMapType::MainMenu:
		OpenWidget(UI_MainMenu, EWidgetType::Base, EInputModeType::UIOnly);
		break;

	case EMapType::Hotel:
		OpenWidget(UI_InGame, EWidgetType::Base, EInputModeType::GameOnly);
		break;
	}
}

#pragma endregion