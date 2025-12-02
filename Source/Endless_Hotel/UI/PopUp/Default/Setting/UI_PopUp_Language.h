// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUp/Default/UI_PopUp_Default.h"
#include "UI/Button/Setting/UI_Button_Setting.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Delegates/DelegateCombinations.h"
#include "UI_PopUp_Language.generated.h"

#pragma region Declare

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSettingLanguage, FButtonInfo, Value);

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API UUI_PopUp_Language : public UUI_PopUp_Default
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
	FSettingSaveData SettingData;

#pragma endregion

#pragma region Button

protected:
	UFUNCTION()
	void ButtonClick_Language(FButtonInfo Value);

	UFUNCTION()
	void ButtonClick_Apply();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_Apply;

#pragma endregion

};