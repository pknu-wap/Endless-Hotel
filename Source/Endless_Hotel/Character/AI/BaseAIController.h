// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

#pragma region Declare

class UAIPerceptionComponent;
class UAISenseConfig_Sight;

#pragma endregion


UCLASS()
class ENDLESS_HOTEL_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

#pragma region Base

public:
	ABaseAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

#pragma endregion

#pragma region Setting

protected:
	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = "AI|Perception")
	TObjectPtr<UAIPerceptionComponent> Perception;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UAISenseConfig_Sight> SightConfig;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BTAsset;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBlackboardData> BBAsset;

#pragma endregion

};
