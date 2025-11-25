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

UUI_Base* UUI_Controller::OpenWidget(const EWidgetType& WidgetType, TSubclassOf<UUI_Base> WidgetClass, const EInputModeType& InputMode)
{
	UUI_Base* OpenedWidget = CreateWidget<UUI_Base>(GetWorld(), WidgetClass);

	FPopUpWidget PopUpWidget;
	PopUpWidget.WidgetType = WidgetType;
	PopUpWidget.PopUpWidget = OpenedWidget;

	switch (WidgetType)
	{
	case EWidgetType::Base:
	{
		if (BaseWidget)
		{
			BaseWidget->RemoveFromViewport();
			BaseWidget = nullptr;
		}
		BaseWidget = OpenedWidget;
		BaseWidget->AddToViewport(BaseWidget_ZOrder);
		break;
	}
	default:
	{
		AdjustPopUpZOrder(true);
		PopUpWidgets.Add(PopUpWidget);
		if (PopUpWidget.WidgetType == EWidgetType::PopUp)
		{
			PopUpWidget.PopUpWidget->AddToViewport(PopUpWidget_ZOrder);
			break;
		}
		GEngine->GameViewport->AddViewportWidgetContent(PopUpWidget.PopUpWidget->TakeWidget(), PopUpWidget_ZOrder);
		break;
	}
	}

	SetInputMode(InputMode);

	return OpenedWidget;
}

void UUI_Controller::CloseWidget(const EWidgetType& WidgetType, const EInputModeType& InputMode)
{
	switch (WidgetType)
	{
	case EWidgetType::Base:
	{
		if (!BaseWidget)
		{
			return;
		}
		BaseWidget->RemoveFromViewport();
		BaseWidget = nullptr;
		break;
	}
	default:
	{
		if (PopUpWidgets.IsEmpty())
		{
			return;
		}
		FPopUpWidget PopUpWidget = PopUpWidgets[PopUpWidget_ZOrder - 1];
		if (PopUpWidget.WidgetType == EWidgetType::PopUp)
		{
			PopUpWidget.PopUpWidget->RemoveFromViewport();
		}
		else
		{
			GEngine->GameViewport->RemoveViewportWidgetContent(PopUpWidget.PopUpWidget->TakeWidget());
		}
		AdjustPopUpZOrder(false);
		break;
	}
	}

	SetInputMode(InputMode);
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
		if (PopUpWidget)
		{
			return;
		}

		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;

		break;
	}
	case EInputModeType::UIOnly:
	{
		FInputModeUIOnly InputMode;

		if (!PopUpWidget)
		{
			InputMode.SetWidgetToFocus(BaseWidget->TakeWidget());
		}
		else
		{
			InputMode.SetWidgetToFocus(PopUpWidget->TakeWidget());
		}

		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;

		break;
	}
	case EInputModeType::GameAndUI:
	{
		FInputModeGameAndUI InputMode;

		if (!PopUpWidget)
		{
			InputMode.SetWidgetToFocus(BaseWidget->TakeWidget());
		}
		else
		{
			InputMode.SetWidgetToFocus(PopUpWidget->TakeWidget());
		}

		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;

		break;
	}
	}
}

#pragma endregion

#pragma region Adjust

void UUI_Controller::AdjustPopUpZOrder(bool bUp)
{
	const int32 Max_ZOrder = 100;
	const int32 Min_ZOrder = 1;

	if (bUp)
	{
		PopUpWidget_ZOrder = FMath::Clamp(PopUpWidget_ZOrder + 1, Min_ZOrder, Max_ZOrder);
		return;
	}

	PopUpWidget_ZOrder = FMath::Clamp(PopUpWidget_ZOrder - 1, Min_ZOrder, Max_ZOrder);
}

#pragma endregion

#pragma region Widget

void UUI_Controller::OpenMapBaseWidget()
{
	switch (UEHGameInstance::CurrentMap)
	{
	case EMapType::MainMenu:
		OpenBaseWidget(UI_MainMenu);
		break;

	case EMapType::Hotel:
		OpenBaseWidget(UI_InGame, EInputModeType::GameOnly);
		break;
	}
}

#pragma endregion