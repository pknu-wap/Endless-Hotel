// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include "Type/UI/Type_UI_Setting.h"
#include <CoreMinimal.h>
#include <UI_PopUp_Option.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_Option : public UUI_PopUp_Base
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

#pragma endregion

#pragma region Input

public:
	virtual void Input_ESC() override {}

#pragma endregion

#pragma region ComboBox

protected:
	UPROPERTY()
	TObjectPtr<class UUI_ComboBox_Setting> ComboBox_Default;

	UPROPERTY(EditAnywhere, Category = "Setting|ComboBox")
	TArray<EOptionValue> ComboBoxOptions;

#pragma endregion

#pragma region Highlight

public:
	void HighlightOptions();

#pragma endregion

};