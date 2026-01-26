// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/Button/UI_Button_Base.h"
#include "Type/UI/Type_UI_Setting.h"
#include <CoreMinimal.h>
#include <Delegates/DelegateCombinations.h>
#include <UI_Button_Option.generated.h>

#pragma region Declare

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHighlightEvent, FOptionInfo, TargetInfo);

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API UUI_Button_Option : public UUI_Button_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

#pragma endregion

#pragma region Setting

protected:
	UPROPERTY()
	TWeakObjectPtr<class UGameUserSettings> SettingHandle;

#pragma endregion

#pragma region Option

protected:
	UPROPERTY(EditAnywhere, Category = "Setting|Option")
	FOptionInfo OptionInfo;

#pragma endregion

#pragma region Click

protected:
	UFUNCTION()
	void Click_Button();

#pragma endregion

#pragma region Highlight

protected:
	UFUNCTION()
	void Highlight(FOptionInfo TargetInfo);

protected:
	static FHighlightEvent HighlightEvent;

	UPROPERTY(EditAnywhere, Category = "Highlight")
	FLinearColor Color_Highlight;

	UPROPERTY(EditAnywhere, Category = "Highlight")
	FLinearColor Color_Default;

#pragma endregion

#pragma region Screen

protected:
	void SetOption_Resolution();

#pragma endregion

};