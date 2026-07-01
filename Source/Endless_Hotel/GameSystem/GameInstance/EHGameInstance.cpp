// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/GameInstance/EHGameInstance.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/HUD/Loading/UI_HUD_Loading.h"
#include "Asset/DataAsset/Level/PDA_Level.h"
#include "GameSystem/SaveGame/SaveManager.h"
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

	OnDataLayerChanged.Broadcast(CurrentDataLayer);
}

#pragma endregion

#pragma region Game

void UEHGameInstance::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}

#pragma endregion

#pragma region Data Layer

void UEHGameInstance::SwitchDataLayer(const EMapDataLayer& TargetDataLayer, bool bNotifyDelegate)
{
	if (CurrentDataLayer == TargetDataLayer)
	{
		return;
	}

	UDataLayerAsset* DLA_Active = GetDataLayerAsset(TargetDataLayer);
	UDataLayerAsset* DLA_Deactive = GetDataLayerAsset(CurrentDataLayer);

	UDataLayerSubsystem* Subsystem = GetWorld()->GetSubsystem<UDataLayerSubsystem>();

	UDataLayerInstance* DLI_Active = Subsystem->GetDataLayerInstance(DLA_Active);
	UDataLayerInstance* DLI_Deactive = Subsystem->GetDataLayerInstance(DLA_Deactive);

	Subsystem->SetDataLayerRuntimeState(DLI_Active, EDataLayerRuntimeState::Activated);
	Subsystem->SetDataLayerRuntimeState(DLI_Deactive, EDataLayerRuntimeState::Loaded);

	CurrentDataLayer = TargetDataLayer;

	if (bNotifyDelegate)
	{
		OnDataLayerChanged.Broadcast(CurrentDataLayer);
	}
}

void UEHGameInstance::SwitchDataLayerWithLoading(const EMapDataLayer& TargetDataLayer, bool bNotifyDelegate)
{
	if (CurrentDataLayer == TargetDataLayer)
	{
		return;
	}

	auto* UICon = GetSubsystem<UUI_Controller>();
	auto* UI_Loading = Cast<UUI_HUD_Loading>(UICon->OpenWidget(EWidgetType::HUD_Loading));

	GetWorld()->GetTimerManager().SetTimer(SwitchHandle, FTimerDelegate::CreateWeakLambda(this, [this, TargetDataLayer, bNotifyDelegate, UI_Loading]()
		{
			if (UI_Loading->IsLoadingCompleted())
			{
				SwitchDataLayer(TargetDataLayer, bNotifyDelegate);
				GetWorld()->GetTimerManager().ClearTimer(SwitchHandle);
			}
		}), 0.1f, true);
}

UDataLayerAsset* UEHGameInstance::GetDataLayerAsset(const EMapDataLayer& Target)
{
	switch (Target)
	{
	case EMapDataLayer::Lobby:
		return PDA_Map->DL_Lobby.LoadSynchronous();

	case EMapDataLayer::Hotel:
		return PDA_Map->DL_Hotel.LoadSynchronous();

	case EMapDataLayer::Fire:
		return PDA_Map->DL_Fire.LoadSynchronous();

	case EMapDataLayer::Maze:
		return PDA_Map->DL_Maze.LoadSynchronous();

	case EMapDataLayer::Choice:
		return PDA_Map->DL_Choice.LoadSynchronous();
	}

	return nullptr;
}

#pragma endregion