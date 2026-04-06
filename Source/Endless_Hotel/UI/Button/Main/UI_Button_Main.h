// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/Button/UI_Button_Base.h"
#include "Type/UI/Type_UI_Title.h"
#include <CoreMinimal.h>
#include <UI_Button_Main.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Button_Main : public UUI_Button_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void SynchronizeProperties() override;

#pragma endregion

#pragma region Type

protected:
	UPROPERTY(EditAnywhere, Category = "Type")
	ETitleButtonType ButtonType;

#pragma endregion

#pragma region Hover

protected:
	UFUNCTION()
	void Hover_Button();

	UFUNCTION()
	void Unhover_Button();

#pragma endregion

};