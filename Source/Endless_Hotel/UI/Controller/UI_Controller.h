// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/UI/Type_UI.h"
#include <Components/PanelWidget.h>
#include <Components/PanelSlot.h>
#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <UI_Controller.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UUI_Controller : public UGameInstanceSubsystem
{
	GENERATED_BODY()

#pragma region Open & Close

public:
	class UUI_Base* OpenWidget(const EWidgetType& WidgetType, float Duration = 0.01f);
	void CloseWidget();

private:
	void CloseAllWidgets();

	void SetGamePause();

#pragma endregion

#pragma region Show

public:
	void ShowHUDWidget(bool bShow);
	void ShowPopUpWidget(bool bShow);

#pragma endregion

#pragma region Child

public:
	template <typename WidgetType, typename OuterType, typename OuterSlotType>
	WidgetType* MakeChildWidget(OuterType* Outer, TSubclassOf<class UUI_Base> Class, ESlateSizeRule::Type Rule = ESlateSizeRule::Fill, float Size = 1.f);

#pragma endregion

#pragma region Cache

public:
	class UUI_Base* GetHUDWidget() { return CachedWidgets[WidgetStack[0]]; }
	class UUI_Base* GetPopUpWidget() { return CachedWidgets[WidgetStack.Top()]; }
	class UUI_Base* GetCachedWidget(const EWidgetType& WidgetType) { return CachedWidgets[WidgetType]; }

private:
	UPROPERTY()
	TMap<EWidgetType, TObjectPtr<class UUI_Base>> CachedWidgets;

	TArray<EWidgetType> WidgetStack;

#pragma endregion

#pragma region Input

private:
	void SetInputMode(const EWidgetInputMode& InputMode);

#pragma endregion

#pragma region Data

private:
	void LoadWidgetDataAsset(const EWidgetType& WidgetType);

	UFUNCTION()
	void OnLoadedWidgetDataAsset(FPrimaryAssetId DataAssetID, EWidgetType WidgetType);

private:
	UPROPERTY()
	TObjectPtr<class UPDA_Widget> PDA_Widget;

#pragma endregion

#pragma region SubTitle

public:
	void ShowSubTitle(FText SubTitle, float Delay, float Duration);

#pragma endregion

};

#pragma region Inline

template <typename WidgetType, typename OuterType, typename OuterSlotType>
FORCEINLINE WidgetType* UUI_Controller::MakeChildWidget(OuterType* Outer, TSubclassOf<class UUI_Base> Class, ESlateSizeRule::Type Rule, float Size)
{
	WidgetType* ChildWidget = CreateWidget<WidgetType>(Outer, Class);
	ChildWidget->ActiveWidget();
	ChildWidget->ShowWidget();

	FSlateChildSize SlateChildSize = FSlateChildSize(Rule);
	SlateChildSize.Value = Size;
	OuterSlotType* PanelSlot = Cast<OuterSlotType>(Outer->AddChild(ChildWidget));
	PanelSlot->SetSize(SlateChildSize);

	return ChildWidget;
}

#pragma endregion