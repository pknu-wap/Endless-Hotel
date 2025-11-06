// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindPlayerPos.generated.h"

UCLASS()
class ENDLESS_HOTEL_API UBTTask_FindPlayerPos : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_FindPlayerPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
