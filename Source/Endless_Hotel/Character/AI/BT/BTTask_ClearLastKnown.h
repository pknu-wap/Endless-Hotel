// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ClearLastKnown.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESS_HOTEL_API UBTTask_ClearLastKnown : public UBTTaskNode
{
	GENERATED_BODY()
	
#pragma region Base

public:
	UBTTask_ClearLastKnown();

#pragma endregion

#pragma region Task

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

#pragma endregion

};
