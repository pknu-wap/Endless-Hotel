// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckAttack.generated.h"

UCLASS()
class ENDLESS_HOTEL_API UBTDecorator_CheckAttack : public UBTDecorator
{
	GENERATED_BODY()
	
#pragma region Base

public:
	UBTDecorator_CheckAttack();

protected:

#pragma endregion

#pragma region Range

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ragne")
	float AttackRange = 0.f;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,uint8* NodeMemory) const override;
#pragma endregion

#pragma region Key

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	struct FBlackboardKeySelector TargetKey;

#pragma endregion

};
