// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/Level/Type_Level.h"
#include "UI/HUD/UI_HUD_Base.h"
#include <CoreMinimal.h>
#include <UI_HUD_Loading.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_HUD_Loading : public UUI_HUD_Base
{
	GENERATED_BODY()

#pragma region Show

public:
	virtual void ShowWidget() override;

#pragma endregion

#pragma region Loading

public:
	bool IsLoadingCompleted();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUI_Slider_Loading> Slider_Loading;

#pragma endregion

};