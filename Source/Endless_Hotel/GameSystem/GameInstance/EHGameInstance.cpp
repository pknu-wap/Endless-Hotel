// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/GameInstance/EHGameInstance.h"
#include "UI/Controller/UI_Controller.h"
#include "Asset/DataAsset/Level/PDA_Level.h"
#include <Kismet/GameplayStatics.h>
#include <WorldPartition/WorldPartitionSubsystem.h>
#include <WorldPartition/DataLayer/DataLayerSubsystem.h>

#pragma region Game

void UEHGameInstance::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}

#pragma endregion

#pragma region Level

void UEHGameInstance::LoadLevel(const ELevelType& LevelType)
{
	CurrentLevelType = LevelType;

	auto* UICon = GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(EWidgetType::PopUp_Loading);

	OnLevelLoaded.Broadcast();
}

void UEHGameInstance::OpenLevel()
{
	TSoftObjectPtr<UWorld> TargetWorld = nullptr;

	switch (CurrentLevelType)
	{
	case ELevelType::Hotel:
		TargetWorld = PDA_Map->Level_Hotel;
		break;

	case ELevelType::MainMenu:
		TargetWorld = PDA_Map->Level_MainMenu;
		break;
	}

	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), TargetWorld);

	OnLevelOpened.Broadcast(CurrentLevelType);
}

void UEHGameInstance::LoadDataLayer(const EHotelDataLayer& Layer)
{
	LoadLayer = Layer;

	TargetDataLayer = GetDataLayerAsset(LoadLayer);

	auto* DLSubsystem = GetWorld()->GetSubsystem<UDataLayerSubsystem>();
	auto* DLInstance = DLSubsystem->GetDataLayerInstance(TargetDataLayer);
	DLSubsystem->SetDataLayerRuntimeState(DLInstance, EDataLayerRuntimeState::Loaded);
}

bool UEHGameInstance::SwitchDataLayer()
{
	auto* WPSubsystem = GetWorld()->GetSubsystem<UWorldPartitionSubsystem>();

	if (!WPSubsystem->IsStreamingCompleted())
	{
		return false;
	}

	auto* DLSubsystem = GetWorld()->GetSubsystem<UDataLayerSubsystem>();
	auto* DLInstance = DLSubsystem->GetDataLayerInstance(TargetDataLayer);
	DLSubsystem->SetDataLayerRuntimeState(DLInstance, EDataLayerRuntimeState::Activated);

	TargetDataLayer = GetDataLayerAsset(UnloadLayer);

	DLInstance = DLSubsystem->GetDataLayerInstance(TargetDataLayer);
	DLSubsystem->SetDataLayerRuntimeState(DLInstance, EDataLayerRuntimeState::Unloaded);

	UnloadLayer = LoadLayer;

	return true;
}

UDataLayerAsset* UEHGameInstance::GetDataLayerAsset(const EHotelDataLayer& Target)
{
	switch (Target)
	{
	case EHotelDataLayer::Hotel:
		return PDA_Map->DL_Hotel.LoadSynchronous();

	case EHotelDataLayer::Fire:
		return PDA_Map->DL_Fire.LoadSynchronous();

	case EHotelDataLayer::Maze:
		return PDA_Map->DL_Maze.LoadSynchronous();

	case EHotelDataLayer::Choice:
		return PDA_Map->DL_Choice.LoadSynchronous();
	}

	return nullptr;
}

#pragma endregion