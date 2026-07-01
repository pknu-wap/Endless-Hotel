// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/Read/Manual/Manual.h"
#include "GameSystem/SaveGame/SaveManager.h"

#pragma region MyRegion

void AManual::Interact_Implementation(AEHCharacter* Interacter)
{
	Super::Interact_Implementation(Interacter);

	auto Data = USaveManager::LoadData_Tutorial();
	Data.bReadManual = true;

	USaveManager::SaveData_Tutorial(Data);
}

#pragma endregion