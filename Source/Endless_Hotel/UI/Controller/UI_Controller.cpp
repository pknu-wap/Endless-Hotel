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

#pragma region Open

UUI_Base* UUI_Controller::OpenBaseWidget(TSubclassOf<UUI_Base> WidgetClass, const EInputModeType& InputMode)
{
	if (BaseWidget)
	{
		CloseBaseWidget(InputMode);
	}
	
	BaseWidget = CreateWidget<UUI_Base>(GetWorld(), WidgetClass);
	BaseWidget->AddToViewport(BASE_UI_ZORDER);

	SetInputMode(InputMode);

	return BaseWidget;
}

UUI_PopUp_Base* UUI_Controller::OpenPopUpWidget(TSubclassOf<UUI_PopUp_Base> WidgetClass, const EInputModeType& InputMode)
{
	if (PopUpWidget)
	{
		ClosePopUpWidget(InputMode);
	}

	PopUpWidget = CreateWidget<UUI_PopUp_Base>(GetWorld(), WidgetClass);
	PopUpWidget->AddToViewport(POPUP_UI_ZORDER);

	SetInputMode(InputMode);

	return PopUpWidget;
}

UUI_PopUp_Base* UUI_Controller::OpenStrongPopUpWidget(TSubclassOf<UUI_PopUp_Base> WidgetClass, const EInputModeType& InputMode)
{
	if (PopUpWidget)
	{
		ClosePopUpWidget(InputMode);
	}

	PopUpWidget = CreateWidget<UUI_PopUp_Base>(GetWorld(), WidgetClass);
	GEngine->GameViewport->AddViewportWidgetContent(PopUpWidget->TakeWidget(), POPUP_UI_ZORDER);

	SetInputMode(InputMode);

	return PopUpWidget;
}

#pragma endregion

#pragma region Close

void UUI_Controller::CloseBaseWidget(const EInputModeType& InputMode)
{
	if (!BaseWidget)
	{
		return;
	}

	BaseWidget->RemoveFromViewport();
	BaseWidget = nullptr;

	SetInputMode(InputMode);
}

void UUI_Controller::ClosePopUpWidget(const EInputModeType& InputMode)
{
	if (!PopUpWidget)
	{
		return;
	}

	PopUpWidget->RemoveFromViewport();
	PopUpWidget = nullptr;

	SetInputMode(InputMode);
}

void UUI_Controller::CloseStrongPopUpWidget(const EInputModeType& InputMode)
{
	if (!PopUpWidget)
	{
		return;
	}

	GEngine->GameViewport->RemoveViewportWidgetContent(PopUpWidget->TakeWidget());
	PopUpWidget = nullptr;

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