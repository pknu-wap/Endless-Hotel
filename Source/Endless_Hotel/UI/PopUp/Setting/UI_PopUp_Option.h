// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include "Type/UI/Type_Setting.h"
#include <CoreMinimal.h>
#include <UI_PopUp_Option.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_Option : public UUI_PopUp_Base
{
	GENERATED_BODY()

#pragma region Input

protected:
	virtual void Input_ESC() override {}

#pragma endregion
	 
#pragma region Option

public:
	void InitOption(FOptionList List);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<class UUI_Button_Setting> ButtonClass;

#pragma endregion

#pragma region TextBlock

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextBlock;

#pragma endregion

#pragma region VerticalBox

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UVerticalBox> VerticalBox;

#pragma endregion

};