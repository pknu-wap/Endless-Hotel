// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "GameSystem/GameMode/EHGameMode_Base.h"
#include "EHGameMode_InGame.generated.h"

class AAnomaly_Generator;

UCLASS()
class ENDLESS_HOTEL_API AEHGameMode_InGame : public AEHGameMode_Base
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AAnomaly_Generator> Generator;

protected:
	virtual void BeginPlay() override;
};