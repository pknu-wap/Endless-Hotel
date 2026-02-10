// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Engine/GameInstance.h>
#include <EHGameInstance.generated.h>

#pragma region Declare

UENUM(BlueprintType)
enum class EMapType : uint8
{
	None		UMETA(DisplayName = "None"),
	Loading		UMETA(DisplayName = "Loading"),
	MainMenu	UMETA(DisplayName = "MainMenu"),
	Hotel		UMETA(DisplayName = "Hotel")
};

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API UEHGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
#pragma region Map

public:
	void OpenMap(const EMapType& MapName);
	void QuitGame();

	float GetMapLoadingPercentage();

protected:
	const FName LoadingMapName = TEXT("/Game/EndlessHotel/Map/Loading");
	FName TargetMapName;

#pragma endregion

#pragma region KeyVal

public:
	UPROPERTY(BlueprintReadWrite, Category = "AnomalyData")
	int32 GlobalSelectedKeyIndex = 0;

#pragma endregion

};