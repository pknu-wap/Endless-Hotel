// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <GameFramework/GameModeBase.h>
#include <EHGameMode.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AEHGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AEHGameMode(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Respawn

public:
	void RespawnPlayer();

#pragma endregion

};