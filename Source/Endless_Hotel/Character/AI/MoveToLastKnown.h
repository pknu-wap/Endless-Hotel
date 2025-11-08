// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MoveToLastKnown.generated.h"

UCLASS()
class ENDLESS_HOTEL_API UMoveToLastKnown : public UBTTaskNode
{
	GENERATED_BODY()
	
#pragma region Base

public:
	UMoveToLastKnown();

#pragma endregion

#pragma region Setting

public:

	UPROPERTY(EditAnywhere, Category = "Investigate")
	float SearchRadius = 300.f;

	UPROPERTY(EditAnywhere, Category = "Investigate")
	bool bProjectToNavMesh = true;

	UPROPERTY(EditAnywhere, Category = "Investigate")
	bool bFailIfUnreachable = false;

#pragma endregion

#pragma region Task

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

#pragma endregion
};
