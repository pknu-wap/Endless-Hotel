// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/PopUp/Setting/UI_PopUp_Option.h"
#include <CoreMinimal.h>
#include <UI_PopUp_Option_Screen.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UUI_PopUp_Option_Screen : public UUI_PopUp_Option
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

#pragma endregion

#pragma region Restore

protected:
	void RestoreOptions();

#pragma endregion

#pragma region Resolution

protected:
	UFUNCTION()
	UWidget* GenerateResolutionItem(FName InKey);

	UFUNCTION()
	void OpenCombo_Res();

	UFUNCTION()
	void CloseCombo_Res(FName NameValue, ESelectInfo::Type EnumValue);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UBorder> Border_Combo_Res;

	UPROPERTY(EditAnywhere, Category = "Setting")
	FLinearColor BorderOutlineColor_Normal;

	UPROPERTY(EditAnywhere, Category = "Setting")
	FLinearColor BorderOutlineColor_Focus;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UComboBoxKey> Combo_Resolution;

#pragma endregion

};