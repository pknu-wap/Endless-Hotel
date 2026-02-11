// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameSystem/Enum/EnumConverter.h"
#include "GameSystem/Anomaly/Anomaly_Generator.h"
#include "GameSystem/GameMode/EHGameMode.h"
#include "UI/Controller/UI_Controller.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Engine/LevelStreamingDynamic.h>

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
		GetWorld()->SpawnActor<AAnomaly_Generator>(Generator);
		UICon->OpenWidget(UI_HUD_InGame);
		break;

	case ELevelType::MainMenu:
		UICon->OpenWidget(UI_HUD_MainMenu);
		break;
	}

	auto* GameMode = GetWorld()->GetAuthGameMode<AEHGameMode>();
	GameMode->RestartPlayer(GetWorld()->GetFirstPlayerController());

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