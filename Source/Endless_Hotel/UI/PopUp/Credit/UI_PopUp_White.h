// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include <CoreMinimal.h>
#include <UI_PopUp_White.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_White : public UUI_PopUp_Base
{
	GENERATED_BODY()
	
#pragma region Show

private:
	virtual void ShowWidget() override;

#pragma endregion

#pragma region Direction

private:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> WA_White;

#pragma endregion

};