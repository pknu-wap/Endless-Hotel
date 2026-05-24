// Copyright by 2025-2 WAP Game 2 team

#include "UI/Controller/UI_Controller.h"
#include "UI/HUD/InGame/UI_HUD_InGame.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Asset/Manager/EHAssetManager.h"
#include "Asset/DataAsset/Widget/PDA_Widget.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/PlayerController.h>

#pragma region Open & Close

UUI_Base* UUI_Controller::OpenWidget(const EWidgetType& WidgetType)
{
	if (!IsValid(PDA_Widget))
	{
		LoadWidgetDataAsset(WidgetType);
		return nullptr;
	}

	auto WidgetClass = PDA_Widget->GetWidgetClass(WidgetType);

	UUI_Base* CreatedWidget = CreateWidget<UUI_Base>(GetWorld()->GetFirstPlayerController(), WidgetClass.LoadSynchronous());

	switch (CreatedWidget->WidgetLayer)
	{
	case EWidgetLayer::None:
		return CreatedWidget;

	case EWidgetLayer::HUD:
		ClearAllWidget();
		break;

	case EWidgetLayer::PopUp_Pause:
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		break;
	}

	if (!PopUpWidgets.IsEmpty())
	{
		PopUpWidgets[0]->SetVisibility(ESlateVisibility::Hidden);
	}

	CreatedWidget->AddToViewport(Widget_ZOrder);
	PopUpWidgets.Add(CreatedWidget);

	AdjustZOrder(true);
	SetInputMode(CreatedWidget->WidgetInputMode);

	return CreatedWidget;
}

void UUI_Controller::CloseWidget()
{
	if (PopUpWidgets.IsEmpty())
	{
		return;
	}

	switch (PopUpWidgets.Top()->WidgetLayer)
	{
	case EWidgetLayer::None:
	case EWidgetLayer::HUD:
		return;

	case EWidgetLayer::PopUp_Pause:
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		break;
	}

	AdjustZOrder(false);

	PopUpWidgets.Top()->RemoveFromViewport();
	PopUpWidgets.Pop();

	UUI_Base* TopWidget = PopUpWidgets.Top();
	TopWidget->SetVisibility(ESlateVisibility::Visible);

	SetInputMode(TopWidget->WidgetInputMode);
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

void UUI_Controller::SetInputMode(const EWidgetInputMode& InputMode)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	switch (InputMode)
	{
	case EWidgetInputMode::GameOnly:
	{
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
		break;
	}
	case EWidgetInputMode::UIOnly:
	{
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(PopUpWidgets.Top()->TakeWidget());
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
		break;
	}
	case EWidgetInputMode::GameAndUI:
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

#pragma region Data

void UUI_Controller::LoadWidgetDataAsset(const EWidgetType& WidgetType)
{
	if (IsValid(PDA_Widget))
	{
		return;
	}

	TArray<FPrimaryAssetId> DataIDs;

	auto& AssetManager = UEHAssetManager::Get();
	AssetManager.GetPrimaryAssetIdList(FPrimaryAssetType("Widget"), OUT DataIDs);

	FPrimaryAssetId DataID = DataIDs[0];
	AssetManager.LoadPrimaryAsset(DataID, { FName("") }, FStreamableDelegate::CreateUObject(this, &ThisClass::OnLoadedWidgetDataAsset, DataID, WidgetType));
}

void UUI_Controller::OnLoadedWidgetDataAsset(FPrimaryAssetId DataAssetID, EWidgetType WidgetType)
{
	auto& AssetManager = UEHAssetManager::Get();
	PDA_Widget = AssetManager.GetPrimaryAssetObject<UPDA_Widget>(DataAssetID);

	OpenWidget(WidgetType);
}

#pragma endregion

#pragma region SubTitle

void UUI_Controller::ShowSubTitle(FText SubTitle, float Delay, float Duration)
{
	auto* UI_InGame = Cast<UUI_HUD_InGame>(GetCurrentHUDWidget());
	UI_InGame->ShowSubTitle(SubTitle, Delay, Duration);
}

#pragma endregion