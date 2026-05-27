// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/GameInstance/EHGameInstance.h"
#include "UI/Controller/UI_Controller.h"
#include "Asset/DataAsset/Level/PDA_Level.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include <Kismet/GameplayStatics.h>
#include <WorldPartition/WorldPartitionSubsystem.h>
#include <WorldPartition/DataLayer/DataLayerSubsystem.h>
#include <GameFramework/GameUserSettings.h>
#include <Internationalization/Internationalization.h>

#pragma region Base

void UEHGameInstance::Init()
{
	Super::Init();

	auto* Settings = GEngine->GetGameUserSettings();
	Settings->LoadSettings();
	Settings->ApplySettings(false);

	auto Data_Setting = USaveManager::LoadData_Setting();
	auto& CultureSetting = FInternationalization::Get();

	switch (Data_Setting.Language)
	{
	case EOptionValue::English:
		CultureSetting.SetCurrentCulture(TEXT("en-US"));
		break;

	case EOptionValue::Korean:
		CultureSetting.SetCurrentCulture(TEXT("ko-KR"));
		break;
	}
}

#pragma endregion

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
	UICon->OpenWidget(EWidgetType::HUD_Loading);

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

#pragma endregion

#pragma region Data Layer

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

	OnDataLayerChanged.Broadcast(UnloadLayer);

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

#pragma region Demo Timer

void UEHGameInstance::StartDemoTimer()
{
	FTimerHandle DemoHandle;
	GetWorld()->GetTimerManager().SetTimer(DemoHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			auto* UICon = GetSubsystem<UUI_Controller>();
			UICon->OpenWidget(EWidgetType::PopUp_Demo);

			USaveManager::DeleteData_Tutorial();
		}), GameplayTime, false);
}

#pragma endregion