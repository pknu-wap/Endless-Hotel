// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameSystem/Enum/EnumConverter.h"
#include "GameSystem/Anomaly/Anomaly_Generator.h"
#include "GameSystem/GameMode/EHGameMode.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"
#include "UI/Controller/UI_Controller.h"
#include "Anomaly/Base/Anomaly_Base.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Engine/LevelStreamingDynamic.h>
#include <GameFramework/Character.h>

#pragma region Declare

ELevelType UEHGameInstance::CurrentLevelType = ELevelType::Persistent;
FLevelLoaded UEHGameInstance::OnLevelLoaded;

#pragma endregion

#pragma region Level

void UEHGameInstance::OpenLevel(const ELevelType& LevelName, bool bIsFirst)
{
	UnloadCurrentLevel();

	if (!bIsFirst)
	{
		auto* UICon = GetSubsystem<UUI_Controller>();
		UICon->OpenWidget(UI_Loading);
	}

	FString TargetLevelPath = FString::Printf(TEXT("/Game/EndlessHotel/Map/%s"), *EnumConverter::GetEnumAsFString<ELevelType>(LevelName));
	FName TargetLevelName = FName(*TargetLevelPath);

	bool bSuccess = false;
	UWorld* TargetLevel = nullptr;

	switch (LevelName)
	{
	case ELevelType::MainMenu:
		TargetLevel = Level_MainMenu;
		CurrentLevelType = ELevelType::MainMenu;
		break;

	case ELevelType::Hotel:
		TargetLevel = Level_Hotel;
		CurrentLevelType = ELevelType::Hotel;
		break;
	}

	CurrentLevel = ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(GetWorld(), TargetLevel, FVector::ZeroVector, FRotator::ZeroRotator, OUT bSuccess);

	CurrentLevel->SetShouldBeVisible(false);
	CurrentLevel->SetShouldBeLoaded(true);

	CurrentLevel->OnLevelLoaded.Clear();
	CurrentLevel->OnLevelLoaded.AddDynamic(this, &ThisClass::LoadLevelCompleted);

	CurrentLevel->OnLevelShown.Clear();
	CurrentLevel->OnLevelShown.AddDynamic(this, &ThisClass::ShowLevelCompleted);
}

void UEHGameInstance::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}

#pragma endregion

#pragma region Loading

bool UEHGameInstance::IsLevelLoaded()
{
	return CurrentLevel->IsLevelLoaded();
}

void UEHGameInstance::LoadLevelCompleted()
{
	CurrentLevel->SetShouldBeVisible(true);
}

void UEHGameInstance::ShowLevelCompleted()
{
	auto* UICon = GetSubsystem<UUI_Controller>();
	UICon->CloseWidget();

	switch (CurrentLevelType)
	{
	case ELevelType::Hotel:
		SpawnAnomalyGenerator();
		UICon->OpenWidget(UI_HUD_InGame);
		break;

	case ELevelType::MainMenu:
		UICon->OpenWidget(UI_HUD_MainMenu);
		break;
	}

	RelocatePlayer();

	OnLevelLoaded.Broadcast();
}

void UEHGameInstance::UnloadCurrentLevel()
{
	if (!CurrentLevel)
	{
		return;
	}

	CurrentLevel->SetShouldBeLoaded(false);
	CurrentLevel->SetShouldBeVisible(false);
	CurrentLevel = nullptr;
}

#pragma endregion

#pragma region Anomaly

void UEHGameInstance::SpawnAnomalyGenerator()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.OverrideLevel = CurrentLevel->GetLoadedLevel();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Generator = GetWorld()->SpawnActor<AAnomaly_Generator>(GeneratorClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
}

#pragma endregion

#pragma region Spawn

void UEHGameInstance::RelocatePlayer()
{
	UWorld* World = GetWorld();

	auto* GameMode = World->GetAuthGameMode<AEHGameMode>();
	GameMode->RestartPlayer(World->GetFirstPlayerController());

	auto* Subsystem = GetSubsystem<UAnomalyProgressSubSystem>();
	auto* Player = UGameplayStatics::GetPlayerCharacter(World, 0);

	if (!Subsystem->bPassed)
	{
		Player->SetActorTransform(DefaultTransform);
		return;
	}

	FTransform AnomalyTransform = Generator->CurrentAnomaly->PlayerStartTransform;
	Player->SetActorTransform(AnomalyTransform);
}

#pragma endregion