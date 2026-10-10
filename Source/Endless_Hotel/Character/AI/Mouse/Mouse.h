// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Character/AI/BaseAI.h"
#include <CoreMinimal.h>
#include <AIController.h>
#include <Mouse.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AMouse : public ABaseAI
{
	GENERATED_BODY()
	
#pragma region Move

public:
	void RunByEat();
	void RunByJumpScare();

private:
	UFUNCTION()
	void MoveToEatCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

	UFUNCTION()
	void MoveToRunCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Move")
	FVector EatDeadBodyLoc;

	UPROPERTY(EditDefaultsOnly, Category = "Move")
	FVector RunLoc;

#pragma endregion

};