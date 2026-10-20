// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/Acquire/RoomKey/RoomKey.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "GameSystem/SubSystem/EHGameSystem.h"

#pragma region Base

void ARoomKey::BeginPlay()
{
	Super::BeginPlay();

	bool bActive = !USaveManager::LoadData_Progression().bHasKey;
	Object->SetVisibility(bActive);
	Component_Interact->ActiveInteract(bActive);

	auto* GameSystem = GetGameInstance()->GetSubsystem<UEHGameSystem>();
	GameSystem->OnProgressionChanged.AddUObject(this, &ThisClass::OnChangedProgression);
}

#pragma endregion

#pragma region Acquire

void ARoomKey::SaveAcquireData()
{
	FSaveData_Progression Data = USaveManager::LoadData_Progression();
	Data.bHasKey = true;
	USaveManager::SaveData_Progression(Data);
	const auto* GameSys = GetGameInstance()->GetSubsystem<UEHGameSystem>();
	GameSys->OnRoomKeyAcquired.Broadcast();
}

#pragma endregion

#pragma region Progression

void ARoomKey::OnChangedProgression(EGameProgression Target)
{
	bool bActive = !USaveManager::LoadData_Progression().bHasKey;
	Object->SetVisibility(bActive);
	Component_Interact->ActiveInteract(bActive);
}

#pragma endregion