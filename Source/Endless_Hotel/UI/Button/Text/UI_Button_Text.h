// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "UI/Button/UI_Button_Base.h"
#include "UI_Button_Text.generated.h"

UCLASS()
class ENDLESS_HOTEL_API UUI_Button_Text : public UUI_Button_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual TSharedRef<SWidget, ESPMode::ThreadSafe> RebuildWidget() override;

#pragma endregion

#pragma region Button

protected:
	UFUNCTION()
	void OnButtonHovered();

	UFUNCTION()
	void OnButtonUnhovered();

#pragma endregion

};