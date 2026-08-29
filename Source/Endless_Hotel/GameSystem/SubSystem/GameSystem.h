// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <GameSystem.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UGameSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

#pragma region Base

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

#pragma endregion

#pragma region Choose

public:
	uint8 ChooseKeyIndex = 0;

#pragma endregion

#pragma region Reset

public:
	void ResetGameSystem();

#pragma endregion
};
