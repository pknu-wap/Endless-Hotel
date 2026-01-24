// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <BehaviorTree/BTTaskNode.h>
#include <BTTask_Attack.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()
	
#pragma region Base

public:
	UBTTask_Attack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
#pragma endregion

};
