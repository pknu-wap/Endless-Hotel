// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/GameMode/EHGameMode.h"
#include "GameSystem/GameInstance/EHGameInstance.h"

#pragma region Base

AEHGameMode::AEHGameMode(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEHGameMode::BeginPlay()
{
	Super::BeginPlay();

	auto* GameInstance = GetGameInstance<UEHGameInstance>();
	GameInstance->OpenLevel(ELevelType::MainMenu, true);
}

#pragma endregion

#pragma region Respawn

void AEHGameMode::RespawnPlayer()
{
	RestartPlayer(GetWorld()->GetFirstPlayerController());
}

#pragma endregion