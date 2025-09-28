// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Default/Setting/UI_PopUp_Setting.h"
#include "UI/Controller/UI_Controller.h"
#include "GameFramework/GameUserSettings.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Components/HorizontalBox.h"
#include "Components/Button.h"
#include "Sound/SoundClass.h"
#include "Kismet/GameplayStatics.h"

#pragma region Delegate

FSettingGrapic UUI_PopUp_Setting::SettingGrapic;
FSettingLanguage UUI_PopUp_Setting::SettingLanguage;
FSettingResolution UUI_PopUp_Setting::SettingResolution;
FSettingScreen UUI_PopUp_Setting::SettingScreen;

#pragma endregion

#pragma region Base

void UUI_PopUp_Setting::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SettingHandle = UGameUserSettings::GetGameUserSettings();

	SettingGrapic.AddDynamic(this, &ThisClass::ButtonClick_Grapic);
	SettingLanguage.AddDynamic(this, &ThisClass::ButtonClick_Language);
	SettingResolution.AddDynamic(this, &ThisClass::ButtonClick_Resolution);
	SettingScreen.AddDynamic(this, &ThisClass::ButtonClick_Screen);

	Button_Cancel->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
	Button_Apply->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Apply);
}

void UUI_PopUp_Setting::NativeConstruct()
{
	Super::NativeConstruct();

	USaveManager* SaveManager = Cast<USaveManager>(UGameplayStatics::LoadGameFromSlot(TEXT("Save_Setting"), 0));
	FSettingSaveData SaveData = SaveManager->LoadSettingData();

	Value_Grapic = SaveData.Grapic;
	Value_Language = SaveData.Language;
	Value_Resolution = SaveData.Resolution;
	Value_Screen = static_cast<EWindowMode::Type>(SaveData.Screen);
	Value_Sound = SaveData.Sound;
}

#pragma endregion

#pragma region Click

void UUI_PopUp_Setting::ButtonClick_Grapic(int32 Value, int32 Index)
{
	Value_Grapic = Value;
}

void UUI_PopUp_Setting::ButtonClick_Language(FString Value, int32 Index)
{
	Value_Language = Value;
}

void UUI_PopUp_Setting::ButtonClick_Resolution(FIntPoint Value, int32 Index)
{
	Value_Resolution = Value;
}

void UUI_PopUp_Setting::ButtonClick_Screen(EWindowMode::Type Value, int32 Index)
{
	Value_Screen = Value;
}

void UUI_PopUp_Setting::SliderClick_Sound(float Value)
{
	Value_Sound = Value;
}

void UUI_PopUp_Setting::ButtonClick_Apply()
{
	SettingHandle->SetOverallScalabilityLevel(Value_Grapic);
	FInternationalization::Get().SetCurrentCulture(Value_Language);
	SettingHandle->SetScreenResolution(Value_Resolution);
	SettingHandle->SetFullscreenMode(Value_Screen);
	SoundMaster->Properties.Volume = Value_Sound;

	SettingHandle->ApplySettings(false);
	SettingHandle->SaveSettings();

	USaveManager* SaveManager = Cast<USaveManager>(UGameplayStatics::LoadGameFromSlot(TEXT("Save_Setting"), 0));
	FSettingSaveData SaveData;

	SaveData.Grapic = Value_Grapic;
	SaveData.Language = Value_Language;
	SaveData.Resolution = Value_Resolution;
	SaveData.Screen = Value_Screen;
	SaveData.Sound = Value_Sound;

	SaveManager->SaveSettingData(SaveData);
}

#pragma endregion

#pragma region Input

void UUI_PopUp_Setting::Input_ESC()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->ClosePopUpWidget(EInputModeType::UIOnly);
}

#pragma endregion