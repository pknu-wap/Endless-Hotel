// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameSystem/Enum/EnumConverter.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>

#pragma region Map

void UEHGameInstance::OpenMap(const EMapType& MapName)
{
	UGameplayStatics::OpenLevel(GetWorld(), LoadingMapName, true);

	FString TargetMapPath = FString::Printf(TEXT("/Game/EndlessHotel/Map/%s"), *EnumConverter::GetEnumAsFString<EMapType>(MapName));
	TargetMapName = FName(*TargetMapPath);

	LoadPackageAsync(TargetMapPath, FLoadPackageAsyncDelegate::CreateWeakLambda(this, [this, MapName](const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result)
		{
			if (Result == EAsyncLoadingResult::Succeeded)
			{
				UGameplayStatics::OpenLevel(GetWorld(), TargetMapName, true);
			}
		}), 0, PKG_ContainsMap);
}

void UEHGameInstance::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}

float UEHGameInstance::GetMapLoadingPercentage()
{
	if (TargetMapName.IsNone())
	{
		return 0.f;
	}

	return GetAsyncLoadPercentage(TargetMapName) / 100.f;
}

#pragma endregion