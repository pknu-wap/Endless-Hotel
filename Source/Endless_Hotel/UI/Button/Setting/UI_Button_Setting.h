// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/Button/UI_Button_Base.h"
#include "Type/UI/Type_Setting.h"
#include <CoreMinimal.h>
#include <Delegates/DelegateCombinations.h>
#include <UI_Button_Setting.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Button_Setting : public UUI_Button_Base
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

#pragma endregion

#pragma region Setting

public:
	UPROPERTY(EditAnywhere, Category = "Setting")
	FSettingCategory SettingInfo;

#pragma endregion

#pragma region Click

public:
	void ClickCategoryButton();

protected:
	UFUNCTION()
	void Click_Button();

#pragma endregion

#pragma region Highlight

protected:
	UFUNCTION()
	void Highlight(FSettingCategory TargetInfo);

protected:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHighlightSetting, FSettingCategory, TargetInfo);
	static FHighlightSetting OnHighlight;

	UPROPERTY(EditAnywhere, Category = "Highlight")
	bool bIsSideButton = false;

	UPROPERTY(EditAnywhere, Category = "Highlight")
	FLinearColor Color_Highlight;

	UPROPERTY(EditAnywhere, Category = "Highlight")
	FLinearColor Color_Default;

#pragma endregion

};