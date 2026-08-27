// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/Button/UI_Button_Base.h"
#include <CoreMinimal.h>
#include <UI_Button_Text.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UUI_Button_Text : public UUI_Button_Base
{
	GENERATED_BODY()
	
#pragma region Button

private:
	UFUNCTION()
	void ButtonHover();

	UFUNCTION()
	void ButtonUnhover();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Hover")
	FString Color_Hover;

	UPROPERTY(EditDefaultsOnly, Category = "Hover")
	FString Color_Unhover;

#pragma endregion

};