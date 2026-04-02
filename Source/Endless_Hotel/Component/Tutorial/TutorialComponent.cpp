// Copyright by 2026-1 WAP Game 2 team

#include "Component/Tutorial/TutorialComponent.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "UI/Tutorial/UI_Tutorial.h"
#include <Components/WidgetComponent.h>

#pragma region Base

void UTutorialComponent::BeginPlay()
{
	Super::BeginPlay();

	Comp_Widget = Owner->FindComponentByTag<UWidgetComponent>(FName("Tutorial"));
	Comp_Widget->InitWidget();

	auto* UI_Tutorial = Cast<UUI_Tutorial>(Comp_Widget->GetUserWidgetObject());
	UI_Tutorial->SetTargetName(TargetName);

	ShowTutorialWidget();
}

#pragma endregion

#pragma region Widget

void UTutorialComponent::ShowTutorialWidget()
{
	FSaveData_Tutorial Data = USaveManager::LoadData_Tutorial();

	if (!Data.bIsFirstPlay)
	{
		Comp_Widget->SetVisibility(false);
		return;
	}

	constexpr float DisappearDuration = 10.f;

	FTimerHandle DisappearHandle;
	GetWorld()->GetTimerManager().SetTimer(DisappearHandle, this, &ThisClass::DisappearTutorialWidget, DisappearDuration, false);
}

void UTutorialComponent::DisappearTutorialWidget()
{
	FSaveData_Tutorial Data = USaveManager::LoadData_Tutorial();
	Data.bIsFirstPlay = false;

	USaveManager::SaveData_Tutorial(Data);

	Comp_Widget->SetVisibility(false);
}

#pragma endregion