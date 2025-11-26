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
	FPopUpWidget PopUpWidget;
	PopUpWidget.WidgetType = WidgetType;
	PopUpWidget.PopUpWidget = CreateWidget<UUI_Base>(GetWorld(), WidgetClass);

	PopUpWidgets.Add(PopUpWidget);

	switch (WidgetType)
	{
	case EWidgetType::PopUpStrong:
		GEngine->GameViewport->AddViewportWidgetContent(PopUpWidget.PopUpWidget->TakeWidget(), PopUpWidget_ZOrder);
		break;

	default:
		PopUpWidget.PopUpWidget->AddToViewport(PopUpWidget_ZOrder);
		break;
	}

	SetInputMode(InputMode);
	AdjustPopUpZOrder(true);

	return PopUpWidget.PopUpWidget;
}

void UUI_Controller::CloseWidget(const EInputModeType& InputMode)
{
	if (PopUpWidgets.IsEmpty())
	{
		return;
	}

	AdjustPopUpZOrder(false);
	SetInputMode(InputMode);

	FPopUpWidget PopUpWidget = PopUpWidgets[PopUpWidget_ZOrder];

	PopUpWidgets.RemoveAt(PopUpWidget_ZOrder);

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
		InputMode.SetWidgetToFocus(PopUpWidgets[PopUpWidget_ZOrder].PopUpWidget->TakeWidget());
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
		break;
	}
	case EInputModeType::GameAndUI:
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(PopUpWidgets[PopUpWidget_ZOrder].PopUpWidget->TakeWidget());
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
	constexpr int32 Max_ZOrder = 100;
	constexpr int32 Min_ZOrder = 1;

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
		OpenWidget(EWidgetType::Base, UI_MainMenu);
		break;

	case EMapType::Hotel:
		OpenWidget(EWidgetType::Base, UI_InGame, EInputModeType::GameOnly);
		break;
	}
}

#pragma endregion