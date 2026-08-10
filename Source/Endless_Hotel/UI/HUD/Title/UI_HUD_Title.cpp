// Copyright by 2025-2 WAP Game 2 team

#include "UI/HUD/Title/UI_HUD_Title.h"
#include "UI/Controller/UI_Controller.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "Player/Camera/EHPlayerCameraManager.h"
#include <Components/AudioComponent.h>
#include <Components/Image.h>
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>

#pragma region Base

void UUI_HUD_Title::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Start->OnClicked.AddDynamic(this, &ThisClass::Click_Start);
	Button_Setting->OnClicked.AddDynamic(this, &ThisClass::Click_Setting);
	Button_Quit->OnClicked.AddDynamic(this, &ThisClass::Click_Quit);
}

#pragma endregion

#pragma region Show

void UUI_HUD_Title::ShowWidget()
{
	Super::ShowWidget();

	SetLogoImage();

	if (!IsValid(AC))
	{
		AC = UGameplayStatics::CreateSound2D(GetWorld(), SW_BGM);
		AC->OnAudioFinished.AddUniqueDynamic(this, &ThisClass::PlayBGM);
		PlayBGM();
	}
}

#pragma endregion

#pragma region Click

void UUI_HUD_Title::Click_Start()
{
	switch (USaveManager::LoadData_Progression().Progression)
	{
	case EGameProgression::CheckIn:
	{
		constexpr float Duration = 2.f;

		auto* CameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
		CameraManager->PossessCameraToPlayer(Duration);

		SetVisibility(ESlateVisibility::Hidden);

		FTimerHandle DelayHandle;
		GetWorld()->GetTimerManager().SetTimer(DelayHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
			{
				auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
				UICon->OpenWidget(EWidgetType::HUD_InGame);
			}), Duration, false);
		break;
	}
	default:
	{
		UEHGameInstance* GameInstance = GetGameInstance<UEHGameInstance>();
		GameInstance->SwitchDataLayerWithLoading(EMapDataLayer::Hotel);
		break;
	}
	}
}

void UUI_HUD_Title::Click_Setting()
{
	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(EWidgetType::PopUp_Setting);
}

void UUI_HUD_Title::Click_Quit()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(EWidgetType::PopUp_QuitCheck);
}

#pragma endregion

#pragma region Hover

void UUI_HUD_Title::PlayButtonAnim_Hover(ETitleButtonType ButtonType)
{
	switch (ButtonType)
	{
	case ETitleButtonType::Start:
		PlayAnimation(Anim_Hover_Start);
		break;

	case ETitleButtonType::Setting:
		PlayAnimation(Anim_Hover_Setting);
		break;

	case ETitleButtonType::Quit:
		PlayAnimation(Anim_Hover_Quit);
		break;
	}
}

void UUI_HUD_Title::PlayButtonAnim_Unhover(ETitleButtonType ButtonType)
{
	switch (ButtonType)
	{
	case ETitleButtonType::Start:
		PlayAnimation(Anim_Unhover_Start);
		break;

	case ETitleButtonType::Setting:
		PlayAnimation(Anim_Unhover_Setting);
		break;

	case ETitleButtonType::Quit:
		PlayAnimation(Anim_Unhover_Quit);
		break;
	}
}

#pragma endregion

#pragma region Logo

void UUI_HUD_Title::SetLogoImage()
{
	if (!USaveManager::LoadData_GameClear())
	{
		return;
	}

	Image_Logo->SetBrushFromTexture(Texture_Clear);
}

#pragma endregion

#pragma region BGM

void UUI_HUD_Title::StopBGM(float Duration)
{
	AC->OnAudioFinished.Clear();
	AC->FadeOut(Duration, 0.f);
	AC = nullptr;
}

void UUI_HUD_Title::PlayBGM()
{
	AC->Play();
}

#pragma endregion