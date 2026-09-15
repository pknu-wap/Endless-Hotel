// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "UI/Button/UI_Button_Base.h"
#include "Type/UI/Type_Setting.h"
#include <CoreMinimal.h>
#include <UI_Button_Category.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Button_Category : public UUI_Button_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Category

public:
	FCategoryButtonInfo GetButtonInfo() { return ButtonInfo; }

	UFUNCTION()
	void Click_Button();

private:
	UPROPERTY(EditAnywhere, Category = "Info")
	FCategoryButtonInfo ButtonInfo;

#pragma endregion

};