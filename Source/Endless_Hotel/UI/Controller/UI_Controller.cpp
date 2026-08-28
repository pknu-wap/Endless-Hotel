// Copyright by 2025-2 WAP Game 2 team

#include "UI/Controller/UI_Controller.h"
#include "UI/HUD/InGame/UI_HUD_InGame.h"
#include "Asset/Manager/EHAssetManager.h"
#include "Asset/DataAsset/Widget/PDA_Widget.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/PlayerController.h>

#pragma region Open & Close

UUI_Base* UUI_Controller::OpenWidget(const EWidgetType& WidgetType, float Duration)
{
	if (WidgetStack.Contains(WidgetType))
	{
		return CachedWidgets[WidgetType];
	}

	if (!IsValid(PDA_Widget))
	{
		LoadWidgetDataAsset(WidgetType);
		return nullptr;
	}

	if (!WidgetStack.IsEmpty())
	{
		UUI_Base* TopWidget = CachedWidgets[WidgetStack.Top()];
		TopWidget->HideWidget();
	}

	UUI_Base* CreatedWidget = nullptr;
	auto WidgetInfo = PDA_Widget->GetWidgetInfo(WidgetType);

	if (CachedWidgets.Contains(WidgetType))
	{
		CreatedWidget = CachedWidgets[WidgetType];
	}
	else
	{
		CreatedWidget = CreateWidget<UUI_Base>(GetWorld()->GetFirstPlayerController(), WidgetInfo.Class.LoadSynchronous());
		CreatedWidget->AddToViewport();
		CreatedWidget->ActiveWidget();
		CachedWidgets.Add(WidgetType, CreatedWidget);
	}

	FTimerHandle ShowHandle;
	GetWorld()->GetTimerManager().SetTimer(ShowHandle, FTimerDelegate::CreateWeakLambda(this, [this, CreatedWidget]()
		{
			CreatedWidget->ShowWidget();
		}), Duration, false);

	UGameplayStatics::SetGamePaused(GetWorld(), false);

	switch (WidgetInfo.Layer)
	{
	case EWidgetLayer::PopUp_Pause:
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		break;

	case EWidgetLayer::HUD:
		CloseAllWidgets();
		break;
	}

	if (!WidgetStack.Contains(WidgetType))
	{
		WidgetStack.Add(WidgetType);
	}	

	SetInputMode(WidgetInfo.InputMode);

	return CreatedWidget;
}

void UUI_Controller::CloseWidget(float Duration)
{
	EWidgetType WidgetType = WidgetStack.Top();
	auto WidgetInfo = PDA_Widget->GetWidgetInfo(WidgetType);

	if (WidgetInfo.Layer == EWidgetLayer::HUD)
	{
		return;
	}

	UUI_Base* TopWidget = CachedWidgets[WidgetType];
	FTimerHandle HideHandle;
	GetWorld()->GetTimerManager().SetTimer(HideHandle, FTimerDelegate::CreateWeakLambda(this, [this, TopWidget]()
		{
			TopWidget->HideWidget();
		}), Duration, false);

	WidgetStack.Pop();

	WidgetType = WidgetStack.Top();
	WidgetInfo = PDA_Widget->GetWidgetInfo(WidgetType);
	TopWidget = CachedWidgets[WidgetStack.Top()];
	TopWidget->ShowWidget();

	UGameplayStatics::SetGamePaused(GetWorld(), false);

	switch (WidgetInfo.Layer)
	{
	case EWidgetLayer::PopUp_Pause:
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		break;
	}

	SetInputMode(WidgetInfo.InputMode);
}

void UUI_Controller::CloseAllWidgets()
{
	for (const EWidgetType& Type : WidgetStack)
	{
		UUI_Base* Target = CachedWidgets[Type];
		Target->HideWidget();
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