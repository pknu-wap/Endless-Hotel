// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <BehaviorTree/Tasks/BTTask_BlackboardBase.h>
#include <BTT_FindPlayer.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UBTT_FindPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
#pragma region Base

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

#pragma endregion

};