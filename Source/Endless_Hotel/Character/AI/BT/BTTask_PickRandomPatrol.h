// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_PickRandomPatrol.generated.h"

UCLASS()
class ENDLESS_HOTEL_API UBTTask_PickRandomPatrol : public UBTTaskNode
{
	GENERATED_BODY()

#pragma region Base

public:
	UBTTask_PickRandomPatrol();

#pragma endregion

#pragma region Key

public:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector PatrolPosKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector LastIndexKey;

#pragma endregion

#pragma region Task

public:
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

#pragma endregion

};
