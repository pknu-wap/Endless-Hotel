// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Character/AI/BaseAIController.h"
#include <CoreMinimal.h>
#include <CrawlChildController.generated.h>

UCLASS()
class ENDLESS_HOTEL_API ACrawlChildController : public ABaseAIController
{
	GENERATED_BODY()
	
#pragma region PlayAnimation

protected:
	UPROPERTY(EditAnywhere, Category = "AnimationConfig");
	TArray<float> AnimationLengths;

	UPROPERTY(EditAnywhere, Category = "AnimationConfig");
	TArray<FTransform> AnimationPositions;

public:
	void FallFromWheelChair();

#pragma endregion

};