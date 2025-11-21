// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_SetState.generated.h"

class UMazeMonsterAnimInstance;

UCLASS()
class ENDLESS_HOTEL_API UBTDecorator_SetState : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_SetState();

protected:
	static UMazeMonsterAnimInstance* GetMonsterAnim(const FBehaviorTreeSearchData& SearchData);
	virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData) override;
	virtual void OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	bool bEntryIsMoving = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	bool bOutIsMoving = false;
};
