// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/UI/Type_UI.h"
#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>
#include <UI_Base.generated.h>

UCLASS(Abstract, Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Base : public UUserWidget
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeDestruct() override;

#pragma endregion

#pragma region Type

public:
	UPROPERTY(EditAnywhere, Category = "Type")
	EWidgetType WidgetType;

	UPROPERTY(EditAnywhere, Category = "Type")
	EInputModeType InputModeType;

#pragma endregion

};