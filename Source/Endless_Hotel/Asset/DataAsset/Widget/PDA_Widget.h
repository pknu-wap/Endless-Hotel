// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Type/UI/Type_UI.h"
#include <CoreMinimal.h>
#include <Engine/DataAsset.h>
#include <PDA_Widget.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UPDA_Widget : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("Widget", GetFName()); }

public:
	TSoftClassPtr<class UUI_Base> GetWidgetClass(const EWidgetType& WidgetType) { return *Map_Widget.Find(WidgetType); }

protected:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TMap<EWidgetType, TSoftClassPtr<class UUI_Base>> Map_Widget;
};