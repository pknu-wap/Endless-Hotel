// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "GameSystem/GameMode/EHGameMode_Base.h"
#include "EHGameMode_InGame.generated.h"

#pragma region Declare

class AAnomaly_Generator;

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API AEHGameMode_InGame : public AEHGameMode_Base
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Anomaly

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AAnomaly_Generator> Generator;

#pragma endregion

};