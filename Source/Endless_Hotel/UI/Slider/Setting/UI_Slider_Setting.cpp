// Copyright by 2025-2 WAP Game 2 team

#include "UI/Slider/Setting/UI_Slider_Setting.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/PopUp/Setting/UI_PopUp_Setting.h"
#include "UI/CheckBox/Setting/UI_CheckBox_Setting.h"
#include "Player/Controller/EHPlayerController.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Sound/SoundController.h"
#include <Kismet/GameplayStatics.h>
#include <Components/TextBlock.h>
#include <Components/Image.h>
#include <Blueprint/WidgetTree.h>

#pragma region Interface

void UUI_Slider_Setting::InitOption(EOptionCategory Category, TArray<FOptionValuePair> Values)
{
	OptionCategory = Category;

	FSaveData_Setting Data = USaveManager::LoadData_Setting();
	float Value = 0.f;

	switch (OptionCategory)
	{
	case EOptionCategory::Master:
		Value = Data.Master;
		break;

	case EOptionCategory::BGM:
		Value = Data.BGM;
		break;

	case EOptionCategory::SFX:
		Value = Data.SFX;
		break;

	case EOptionCategory::Voice:
		Value = Data.Voice;
		break;

	case EOptionCategory::UI:
		Value = Data.UI;
		break;

	case EOptionCategory::Sensitivity:
		Value = Data.Sensitivity;
		break;

	case EOptionCategory::Brightness:
		Value = Data.Brightness;
		break;
	}

	Slide_Slider(Value);

	TArray<UWidget*> Childs;
	WidgetTree->GetChildWidgets(GetRootWidget(), OUT Childs);
	for (auto* Child : Childs)
	{
		if (auto* CheckBox = Cast<UUI_CheckBox_Setting>(Child))
		{
			CheckBox->InitOption(Category, Values);
			break;
		}
	}
}

#pragma endregion

#pragma region Slider

void UUI_Slider_Setting::Slide_Slider(float Value)
{
	Super::Slide_Slider(Value);

	TextBlock->SetText(FText::FromString(FString::FromInt(Value * 100)));

	auto* UI_Setting = GetTypedOuter<UUI_PopUp_Setting>();
	FSaveData_Setting& Data = UI_Setting->GetSettingData();

	auto* SoundCon = GetGameInstance()->GetSubsystem<USoundController>();

	switch (OptionCategory)
	{
	case EOptionCategory::Master:
		Data.Master = Value;
		SoundCon->SetSoundClassValue(ESoundClassType::Master, Value * Data.MuteMaster);
		break;

	case EOptionCategory::BGM:
		Data.BGM = Value;
		SoundCon->SetSoundClassValue(ESoundClassType::BGM, Value * Data.MuteBGM);
		break;

	case EOptionCategory::SFX:
		Data.SFX = Value;
		SoundCon->SetSoundClassValue(ESoundClassType::SFX, Value * Data.MuteSFX);
		break;

	case EOptionCategory::Voice:
		Data.Voice = Value;
		SoundCon->SetSoundClassValue(ESoundClassType::Voice, Value * Data.MuteVoice);
		break;

	case EOptionCategory::UI:
		Data.UI = Value;
		SoundCon->SetSoundClassValue(ESoundClassType::UI, Value * Data.MuteUI);
		break;

	case EOptionCategory::Sensitivity:
	{
		Data.Sensitivity = Value;
		AEHPlayerController* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		PC->SetLookSensitivity(Value);
		break;
	}
	case EOptionCategory::Brightness:
		UImage* Image_Brightness = Cast<UImage>(GetWidgetFromName(TEXT("Image_Brightness")));
		FLinearColor Color = Image_Brightness->GetColorAndOpacity();
		float AlphaValue = 0.05f + Value * 0.95f;
		Color.A = AlphaValue;
		Image_Brightness->SetColorAndOpacity(Color);

		Data.Brightness = Value;
		break;
	}
}

#pragma endregion