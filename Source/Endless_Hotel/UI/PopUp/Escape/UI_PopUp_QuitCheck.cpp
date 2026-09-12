// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Escape/UI_PopUp_QuitCheck.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "Player/Camera/EHPlayerCameraManager.h"
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>

#pragma region Base

void UUI_PopUp_QuitCheck::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Yes->OnClicked.AddDynamic(this, &ThisClass::Click_Yes);
	Button_No->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
	Button_ESC->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
}

#pragma endregion

#pragma region Click

void UUI_PopUp_QuitCheck::Click_Yes()
{
	UEHGameInstance* GameInstance = GetGameInstance<UEHGameInstance>();

	switch (QuitType)
	{
	case EQuitButtonType::Quit:
		GameInstance->QuitGame();
		break;

	case EQuitButtonType::MainMenu:
	{
		GameInstance->SwitchDataLayer(EMapDataLayer::Lobby);

		constexpr float PossessDuration = 0.f;
		auto* CameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
		CameraManager->PossessCamera(ECameraType::Title, PossessDuration);
		break;
	}
	}
}

#pragma endregion