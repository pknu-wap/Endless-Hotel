// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Character/AI/BaseAIController.h"
#include "MazeMonsterController.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AMazeMonsterController : public ABaseAIController
{
	GENERATED_BODY()

#pragma region Base

public:
	AMazeMonsterController();

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Search & Move

protected:
	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus Stimulus);

#pragma endregion

#pragma region Key

public:
	static const FName Key_TargetPlayer;
	static const FName Key_LastKnownPos;
	static const FName Key_PatrolPos;

#pragma endregion
};
