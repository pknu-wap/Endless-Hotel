// Copyright by 2026-1 WAP Game 2 team

#include "UI/HorizontalBox/Title/UI_HorizontalBox_TitleButton.h"
#include "UI/Controller/UI_Controller.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "Player/Camera/EHPlayerCameraManager.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>

#pragma region Base

void UUI_HorizontalBox_TitleButton::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Text_Button->SetText(ButtonName);

	Button->OnClicked.AddDynamic(this, &ThisClass::Click_Button);
	Button->OnHovered.AddDynamic(this, &ThisClass::Hover_Button);
	Button->OnUnhovered.AddDynamic(this, &ThisClass::Unhover_Button);
}

#pragma endregion

#pragma region Click

void UUI_HorizontalBox_TitleButton::Click_Button()
{
	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();

	switch (ButtonType)
	{
	case ETitleButtonType::Start:
	{
		auto* Subsystem = GetGameInstance()->GetSubsystem<UGameSystem>();
		Subsystem->ResetGameSystem();

		constexpr float Duration = 2.f;
		if (USaveManager::LoadData_Progression().Progression == EGameProgression::CheckIn)
		{
			UICon->OpenWidget(EWidgetType::HUD_InGame, Duration);
		}
		else
		{
			UICon->OpenWidget(EWidgetType::HUD_Loading, Duration);

			auto* CameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
			CameraManager->PossessCamera(ECameraType::SandClock, Duration);
		}
		break;
	}
	case ETitleButtonType::Setting:
	{
		UICon->OpenWidget(EWidgetType::PopUp_Setting);
		break;
	}
	case ETitleButtonType::Quit:
	{
		UICon->OpenWidget(EWidgetType::PopUp_QuitCheck);
		break;
	}
	}
}

#pragma endregion

#pragma region Hover

void UUI_HorizontalBox_TitleButton::Hover_Button()
{
	PlayAnimation(Anim_Hover);
}

void UUI_HorizontalBox_TitleButton::Unhover_Button()
{
	PlayAnimation(Anim_Unhover);
}

#pragma endregion