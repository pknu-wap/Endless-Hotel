// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/GameInstance/EHGameInstance.h"
#include "UI/Controller/UI_Controller.h"
#include "Asset/Manager/EHAssetManager.h"
#include "Asset/DataAsset/Level/PDA_Level.h"
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
	FPrimaryAssetId DataAssetID = PDA_Map->GetPrimaryAssetId();

	auto& AssetManager = UEHAssetManager::Get();
	AssetManager.LoadPrimaryAsset(DataAssetID, {BundleName}, FStreamableDelegate::CreateUObject(this, &ThisClass::OnLoadedLevelDataAsset, DataAssetID));
}

void UEHGameInstance::OnLoadedLevelDataAsset(FPrimaryAssetId DataAssetID)
{
	
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

}

void UEHGameInstance::SwitchDataLayer()
{

}

#pragma endregion