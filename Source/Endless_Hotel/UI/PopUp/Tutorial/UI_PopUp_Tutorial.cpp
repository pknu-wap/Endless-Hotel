// Copyright by 2026-1 WAP Game 2 team

#include "UI/PopUp/Tutorial/UI_PopUp_Tutorial.h"
#include "UI/Controller/UI_Controller.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameSystem/SaveGame/SaveManager.h"

#pragma region Base

void UUI_PopUp_Tutorial::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	auto* GameInstance = GetGameInstance<UEHGameInstance>();
	GameInstance->OnLevelOpened.AddDynamic(this, &ThisClass::OpenTutorialWidget);
}

#pragma endregion

#pragma region Tutorial

void UUI_PopUp_Tutorial::OpenTutorialWidget(const ELevelType& LevelType)
{
	auto SaveData = USaveManager::LoadData_Tutorial();

	if (LevelType != ELevelType::Hotel || !SaveData.bIsFirstPlay)
	{
		return;
	}

	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(EWidgetType::PopUp_Tutorial);
}

#pragma endregion