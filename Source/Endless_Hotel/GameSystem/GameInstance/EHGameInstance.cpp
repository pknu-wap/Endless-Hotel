// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameSystem/Enum/EnumConverter.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "Actor/Anomaly/Anomaly_Generator.h"
#include "Anomaly/Base/Anomaly_Event.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/PopUp/Loading/UI_PopUp_Loading.h"
#include "Player/Camera/EHPlayerCameraManager.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>

#pragma region Game

void UEHGameInstance::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}

#pragma endregion

#pragma region Level

void UEHGameInstance::OpenLevel(const ELevelType& LevelName, bool bNeedLoading)
{
	CurrentLevelType = LevelName;
	bIsOpenedLoadingWidget = bNeedLoading;

	UnloadStreamLevel();

	if (bNeedLoading)
	{
		auto* UICon = GetSubsystem<UUI_Controller>();
		UI_Loading = Cast<UUI_PopUp_Loading>(UICon->OpenWidget(UI_Loading_Class));
	}
}

#pragma endregion

#pragma region Loading

bool UEHGameInstance::IsLevelLoaded()
{
	return CurrentStreamLevel->IsLevelLoaded();
}

void UEHGameInstance::LoadStreamLevel()
{
	TSoftObjectPtr<UWorld> TargetLevel = nullptr;

	switch (CurrentLevelType)
	{
	case ELevelType::MainMenu:
		TargetLevel = Level_MainMenu;
		break;

	case ELevelType::Hotel:
		TargetLevel = Level_Hotel;
		break;
	}

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("OnLevelLoaded");
	LatentInfo.Linkage = 0;
	LatentInfo.UUID = __LINE__;

	UGameplayStatics::LoadStreamLevelBySoftObjectPtr(GetWorld(), TargetLevel, false, false, LatentInfo);
}

void UEHGameInstance::OnLevelLoaded()
{
	switch (CurrentLevelType)
	{
	case ELevelType::MainMenu:
		CurrentLevel = Level_MainMenu;
		break;
	case ELevelType::Hotel:
		CurrentLevel = Level_Hotel;
		break;
	}

	CurrentStreamLevel = UGameplayStatics::GetStreamingLevel(GetWorld(), *CurrentLevel.GetAssetName());
	CurrentStreamLevel->OnLevelShown.RemoveAll(this);
	CurrentStreamLevel->OnLevelShown.AddDynamic(this, &ThisClass::OnLevelShown);
	CurrentStreamLevel->SetShouldBeVisible(true);

	LevelLoaded.Broadcast();
}

void UEHGameInstance::OnLevelShown()
{
	if (!bIsOpenedLoadingWidget)
	{
		StartLoadedLevel();
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(StartHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			if (UI_Loading->IsLoadingComplete())
			{
				StartLoadedLevel();
				GetWorld()->GetTimerManager().ClearTimer(StartHandle);
			}
		}), 0.1f, true);
}

void UEHGameInstance::UnloadStreamLevel()
{
	if (!CurrentLevel.IsValid())
	{
		LoadStreamLevel();
		return;
	}

	CurrentStreamLevel->OnLevelHidden.RemoveAll(this);
	CurrentStreamLevel->OnLevelHidden.AddDynamic(this, &ThisClass::OnLevelHidden);
	CurrentStreamLevel->SetShouldBeVisible(false);
}

void UEHGameInstance::OnLevelHidden()
{
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("OnLevelUnloaded");
	LatentInfo.Linkage = 0;
	LatentInfo.UUID = __LINE__;

	UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(GetWorld(), CurrentLevel, LatentInfo, false);

	LevelHidden.Broadcast();
}

void UEHGameInstance::OnLevelUnloaded()
{
	CurrentStreamLevel = nullptr;
	CurrentLevel = nullptr;

	LoadStreamLevel();

	LevelUnloaded.Broadcast();
}

void UEHGameInstance::StartLoadedLevel()
{
	UWorld* World = GetWorld();

	auto* UICon = GetSubsystem<UUI_Controller>();
	UICon->CloseWidget();

	auto* CameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(World, 0));

	switch (CurrentLevelType)
	{
	case ELevelType::Hotel:
		SpawnAnomalyGenerator();
		UICon->OpenWidget(UI_HUD_InGame_Class);
		CameraManager->PossessCamera(UGameplayStatics::GetPlayerCharacter(World, 0));
		break;

	case ELevelType::MainMenu:
		UICon->OpenWidget(UI_HUD_Title_Class);
		CameraManager->PossessCamera(ECameraType::Title);
		break;
	}

	RelocatePlayer();

	LevelShown.Broadcast();
}

#pragma endregion

#pragma region Anomaly

void UEHGameInstance::SpawnAnomalyGenerator()
{
	ULevel* SpawnLevel = CurrentStreamLevel->GetLoadedLevel();
}

#pragma endregion

#pragma region Player

void UEHGameInstance::RelocatePlayer()
{
	auto* Subsystem = GetSubsystem<UGameSystem>();
	auto* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto* PC = Player->GetController();
	Subsystem->SetVerdictMode();
	Subsystem->ApplyVerdict();
	Player->SetActorTransform(DefaultTransform);
}

#pragma endregion