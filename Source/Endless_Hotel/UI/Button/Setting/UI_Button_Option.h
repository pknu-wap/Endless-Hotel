// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/Button/UI_Button_Base.h"
#include "Type/UI/Type_Setting.h"
#include <CoreMinimal.h>
#include <UI_Button_Option.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UUI_Button_Option : public UUI_Button_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Option

public:
	EOptionValue GetValue() { return OptionValue; }
	void SetOptionInfo(EOptionCategory Category, FOptionValuePair Value);

private:
	EOptionCategory OptionCategory;
	EOptionValue OptionValue;

#pragma endregion

#pragma region TextBlock

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextBlock;

#pragma endregion

#pragma region Setting

private:
	UPROPERTY()
	TWeakObjectPtr<class UGameUserSettings> SettingHandle;

#pragma endregion

#pragma region Click

private:
	UFUNCTION()
	void Click_Button();

#pragma endregion

#pragma region Screen

protected:
	void SetOption_Window();
	void SetOption_Aspect();
	void SetOption_Frame();
	void SetOption_VSync();
	void SetOption_HDR();

#pragma endregion

#pragma region Grapic

protected:
	void SetOption_AntiAliasing();
	void SetOption_Shadow();
	void SetOption_Texture();
	void SetOption_PostProcessing();
	void SetOption_Shading();

#pragma endregion

#pragma region Gameplay

protected:
	void SetOption_AnomalyOverlap();
	void SetOption_CameraShake();

#pragma endregion

#pragma region System

protected:
	void PopUpOption_ResetNote();
	void PopUpOption_ResetSetting();

#pragma endregion

};