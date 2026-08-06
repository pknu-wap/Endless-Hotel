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

public:
	void StartWithWheelChair();
	void FallFromWheelChair();

#pragma endregion

#pragma region CrawlChild

protected:
	UPROPERTY(VisibleAnywhere, Category = "CrawlChild")
	TWeakObjectPtr<class ACrawlChild> CrawlChild;

	UPROPERTY(EditAnywhere, Category = "CrawlChild|Seat")
	FTransform SeatOffsetTransform;

	UPROPERTY(EditAnywhere, Category = "CrawlChild|GetOff")
	FTransform GetOffOffsetTransform;

#pragma endregion

};