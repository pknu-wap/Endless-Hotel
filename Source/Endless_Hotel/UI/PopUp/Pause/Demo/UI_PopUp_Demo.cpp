// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Pause/Demo/UI_PopUp_Demo.h"
#include "UI/Controller/UI_Controller.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"
#include "Components/Button.h"

#pragma region Base

void UUI_PopUp_Demo::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Return->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Return);

	UI_Demo = StaticClass();

	auto* Subsystem = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
	Subsystem->GameClearEvent.AddDynamic(this, &ThisClass::OpenDemoWidget);
}

#pragma endregion

#pragma region Button

void UUI_PopUp_Demo::ButtonClick_Return()
{
	UEHGameInstance* GameInstance = GetGameInstance<UEHGameInstance>();
	GameInstance->OpenMap(EMapType::MainMenu);
}

#pragma endregion

#pragma region Clear

void UUI_PopUp_Demo::OpenDemoWidget()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenStrongPopUpWidget(UI_Demo);
}

#pragma endregion