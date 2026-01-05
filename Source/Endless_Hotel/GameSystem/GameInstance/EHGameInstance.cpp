// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameSystem/Enum/EnumConverter.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>

#pragma region Base

void UEHGameInstance::OnStart()
{
	Super::OnStart();

	FString MapName = GetWorld()->GetMapName();
	MapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	if (MapName == TEXT("MainMenu"))
	{
		CurrentMap = EMapType::MainMenu;
	}
	else if (MapName == TEXT("Hotel"))
	{
		CurrentMap = EMapType::Hotel;
	}
	else
	{
		CurrentMap = EMapType::None;
	}
}

#pragma endregion

#pragma region Map

EMapType UEHGameInstance::CurrentMap = EMapType::MainMenu;

void UEHGameInstance::OpenMap(const EMapType& MapName)
{
	CurrentMap = MapName;
	FName TargetMapName = FName(FString::Printf(TEXT("/Game/EndlessHotel/Map/%s"), *EnumConverter::GetEnumAsFString<EMapType>(CurrentMap)));
	UGameplayStatics::OpenLevel(GetWorld(), TargetMapName, true);
}

void UEHGameInstance::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}

#pragma endregion