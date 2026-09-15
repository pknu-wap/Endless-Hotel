// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Type/UI/Type_UI.h"
#include <CoreMinimal.h>
#include <Engine/DataAsset.h>
#include <PDA_Widget.generated.h>

#pragma region Declare

USTRUCT()
struct FWidgetInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSoftClassPtr<class UUI_Base> Class;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	EWidgetLayer Layer = EWidgetLayer::None;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	EWidgetInputMode InputMode = EWidgetInputMode::None;
};

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API UPDA_Widget : public UPrimaryDataAsset
{
	GENERATED_BODY()

#pragma region Data

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("Widget", GetFName()); }

#pragma endregion

#pragma region Widget

public:
	FWidgetInfo GetWidgetInfo(const EWidgetType& WidgetType) { return *Widgets.Find(WidgetType); }

private:
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TMap<EWidgetType, FWidgetInfo> Widgets;

#pragma endregion

};