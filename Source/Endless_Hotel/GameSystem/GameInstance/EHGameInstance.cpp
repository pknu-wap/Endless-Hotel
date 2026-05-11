// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "UI/Controller/UI_Controller.h"
#include "Asset/Manager/EHAssetManager.h"
#include "Asset/DataAsset/Map/PDA_Map.h"
#include <Kismet/GameplayStatics.h>

#pragma region Game

void UEHGameInstance::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}

#pragma endregion

#pragma region Data

void UEHGameInstance::LoadMapDataAsset(const FName& BundleName)
{
	FPrimaryAssetId DataID = DA_Map->GetPrimaryAssetId();

	if (IsValid(DA_Map) && DA_Map_Handles[BundleName]->HasLoadCompleted())
	{
		return;
	}

	DA_Map_Handles.Remove(BundleName);

	auto& AssetManager = UEHAssetManager::Get();
	DA_Map_Handles.Add(BundleName, AssetManager.LoadPrimaryAsset(DataID, { BundleName }));
}

#pragma endregion

#pragma region Level

void UEHGameInstance::LoadLevel(const ELevelType& LevelType)
{
	CurrentLevelType = LevelType;

	LoadMapDataAsset(FName("Level"));

	auto* UICon = GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(UI_Loading_Class);

	OnLevelLoaded.Broadcast();
}

void UEHGameInstance::OpenLevel()
{
	UWorld* World = GetWorld();
	TSoftObjectPtr<UWorld> TargetWorld = nullptr;

	auto* UICon = GetSubsystem<UUI_Controller>();

	switch (CurrentLevelType)
	{
	case ELevelType::Hotel:
		TargetWorld = DA_Map->Level_MainMenu;
		UICon->OpenWidget(UI_HUD_InGame_Class);
		CameraManager->PossessCamera(UGameplayStatics::GetPlayerCharacter(World, 0));
		break;

	case ELevelType::MainMenu:
		TargetWorld = DA_Map->Level_Hotel;
		UICon->OpenWidget(UI_HUD_Title_Class);
		CameraManager->PossessCamera(ECameraType::Title);
		break;
	}

	UGameplayStatics::OpenLevelBySoftObjectPtr(World, TargetWorld);

	auto* GameSystem = GetSubsystem<UGameSystem>();
	GameSystem->SetVerdictMode();
	GameSystem->ApplyVerdict();

	auto* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Player->SetActorTransform(DefaultTransform);

	OnLevelOpened.Broadcast(CurrentLevelType);
}

void UEHGameInstance::LoadDataLayer(const EHotelDataLayer& Layer)
{

}

void UEHGameInstance::SwitchDataLayer()
{

}

#pragma endregion