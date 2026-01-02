// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include "Type/UI/Type_UI.h"
#include "Type/Save/Type_Save.h"
#include <CoreMinimal.h>
#include <Delegates/DelegateCombinations.h>
#include <UI_PopUp_Language.generated.h>

#pragma region Declare

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSettingLanguage, FButtonInfo, Value);

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API UUI_PopUp_Language : public UUI_PopUp_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

#pragma endregion

#pragma region Delegate

public:
	static FSettingLanguage SettingLanguage;

#pragma endregion

#pragma region Data

protected:
	void LoadSettingData();

protected:
	FSettingSaveData SettingData;

#pragma endregion

#pragma region Button

protected:
	UFUNCTION()
	void Click_Language(FButtonInfo Value);

	UFUNCTION()
	void Click_Apply();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text_Current;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UScrollBox> Buttons_Language;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Apply;

#pragma endregion

};