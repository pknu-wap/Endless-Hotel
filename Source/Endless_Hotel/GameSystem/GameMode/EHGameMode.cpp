// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/GameMode/EHGameMode.h"
#include "UI/Controller/UI_Controller.h"

#pragma region Base

AEHGameMode::AEHGameMode(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEHGameMode::BeginPlay()
{
	Super::BeginPlay();

	auto* UI_Con = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UI_Con->OpenWidget(WidgetType);
}

#pragma endregion