// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/UI/Type_UI.h"
#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <UI_Controller.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UUI_Controller : public UGameInstanceSubsystem
{
	GENERATED_BODY()

#pragma region Open & Close

public:
	class UUI_Base* OpenWidget(const EWidgetType& WidgetType);
	void CloseWidget();

private:
	void CloseAllWidgets();

#pragma endregion

#pragma region Show

public:
	void ShowHUDWidget(bool bShow);
	void ShowPopUpWidget(bool bShow);

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