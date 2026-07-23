// Copyright by 2025-2 WAP Game 2 team

#include "UI/Controller/UI_Controller.h"
#include "UI/HUD/InGame/UI_HUD_InGame.h"
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

	if (!WidgetStack.IsEmpty())
	{
		CachedWidgets[WidgetStack.Top()]->HideWidget();
	}

	UUI_Base* CreatedWidget = nullptr;

	if (CachedWidgets.Contains(WidgetType))
	{
		CreatedWidget = CachedWidgets[WidgetType];
	}
	else
	{
		auto WidgetClass = PDA_Widget->GetWidgetClass(WidgetType);
		CreatedWidget = CreateWidget<UUI_Base>(GetWorld()->GetFirstPlayerController(), WidgetClass.LoadSynchronous());
		CreatedWidget->AddToViewport();
		CachedWidgets.Add(WidgetType, CreatedWidget);
	}

	CreatedWidget->ShowWidget();

	switch (CreatedWidget->WidgetLayer)
	{
	case EWidgetLayer::HUD:
		CloseAllWidgets();
		break;
	}

	if (!WidgetStack.Contains(WidgetType))
	{
		WidgetStack.Add(WidgetType);
	}

	bool bNeedPause = CreatedWidget->WidgetLayer == EWidgetLayer::PopUp_Pause;
	UGameplayStatics::SetGamePaused(GetWorld(), bNeedPause);

	SetInputMode(CreatedWidget->WidgetInputMode);

	return CreatedWidget;
}

void UUI_Controller::CloseWidget()
{
	UUI_Base* TopWidget = CachedWidgets[WidgetStack.Top()];

	if (WidgetStack.IsEmpty() || TopWidget->WidgetLayer == EWidgetLayer::HUD)
	{
		return;
	}

	TopWidget->HideWidget();
	WidgetStack.Pop();

	TopWidget = CachedWidgets[WidgetStack.Top()];
	TopWidget->ShowWidget();

	bool bNeedPause = TopWidget->WidgetLayer == EWidgetLayer::PopUp_Pause;
	UGameplayStatics::SetGamePaused(GetWorld(), bNeedPause);

	SetInputMode(TopWidget->WidgetInputMode);
}

void UUI_Controller::CloseAllWidgets()
{
	for (const EWidgetType& Target : WidgetStack)
	{
		CachedWidgets[Target]->HideWidget();
	}

	WidgetStack.Empty();
}

#pragma endregion

#pragma region Show

void UUI_Controller::ShowHUDWidget(bool bShow)
{
	ESlateVisibility SV = bShow ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed;
	GetHUDWidget()->SetVisibility(SV);
}

void UUI_Controller::ShowPopUpWidget(bool bShow)
{
	ESlateVisibility SV = bShow ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed;
	GetPopUpWidget()->SetVisibility(SV);
}

#pragma endregion

#pragma region Input

void UUI_Controller::SetInputMode(const EWidgetInputMode& InputMode)
{
	auto* PC = GetWorld()->GetFirstPlayerController();
	UUI_Base* TopWidget = CachedWidgets[WidgetStack.Top()];

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
		InputMode.SetWidgetToFocus(TopWidget->TakeWidget());
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
		break;
	}
	case EWidgetInputMode::GameAndUI:
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(TopWidget->TakeWidget());
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
		break;
	}
	}
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
	auto* UI_InGame = Cast<UUI_HUD_InGame>(GetHUDWidget());
	UI_InGame->ShowSubTitle(SubTitle, Delay, Duration);
}

#pragma endregion