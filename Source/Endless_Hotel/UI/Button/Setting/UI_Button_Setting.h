// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/Button/UI_Button_Base.h"
#include "Type/UI/Type_UI.h"
#include <CoreMinimal.h>
#include <UI_Button_Setting.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Button_Setting : public UUI_Button_Base
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void SynchronizeProperties() override;

#pragma endregion
	
#pragma region Setting

public:
	UPROPERTY(EditAnywhere)
	FButtonInfo ButtonInfo;

#pragma endregion

#pragma region Click

protected:
	UFUNCTION()
	void ButtonClick();

#pragma endregion

};