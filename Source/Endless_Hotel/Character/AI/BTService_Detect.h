// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Detect.generated.h"

UCLASS()
class ENDLESS_HOTEL_API UBTServiece_Detect : public UBTService
{
	GENERATED_BODY()
public:
	UBTServiece_Detect();
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
