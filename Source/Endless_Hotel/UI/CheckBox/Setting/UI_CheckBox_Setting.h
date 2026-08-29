// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/CheckBox/UI_CheckBox_Base.h"
#include "Interface/UI/OptionInterface.h"
#include <CoreMinimal.h>
#include <UI_CheckBox_Setting.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_CheckBox_Setting : public UUI_CheckBox_Base, public IOptionInterface
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Interface

public:
	virtual void InitOption(EOptionCategory Category, TArray<FOptionValuePair> Values) override;

#pragma endregion

#pragma region Click

private:
	UFUNCTION()
	void Click_CheckBox(bool bIsMute);

#pragma endregion

#pragma region Option

private:
	EOptionCategory OptionCategory = EOptionCategory::None;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image_Off;

#pragma endregion

};