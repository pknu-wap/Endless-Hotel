// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Character/AI/BaseAI.h"
#include "MazeMonster.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESS_HOTEL_API AMazeMonster : public ABaseAI
{
	GENERATED_BODY()

#pragma region Base

public:
	AMazeMonster(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Patrol

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	TArray<TObjectPtr<AActor>> PatrolPoints;

	UPROPERTY(EditAnywhere, Category = "Patrol")
	uint8 CurrentIndex;
#pragma endregion
};
