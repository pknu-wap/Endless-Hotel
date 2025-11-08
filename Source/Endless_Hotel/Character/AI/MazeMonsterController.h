// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MazeMonsterController.generated.h"

#pragma region Declare

class UAIPerceptionComponent;
class UAISenseConfig_Sight;

#pragma endregion


UCLASS()
class ENDLESS_HOTEL_API AMazeMonsterController : public AAIController
{
	GENERATED_BODY()

#pragma region Base

public:
	AMazeMonsterController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Setting

protected:
	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = "AI|Perception")
	TObjectPtr<UAIPerceptionComponent> Perception;

	UPROPERTY()
	TObjectPtr<UAISenseConfig_Sight> SightConfig;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BTAsset;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBlackboardData> BBAsset;

#pragma endregion

#pragma region Search & Move

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus Stimulus);

#pragma endregion

#pragma region Key

public:
	static const FName Key_TargetPlayer;
	static const FName Key_LastKnownPos;
	static const FName Key_PatrolPos;

#pragma endregion

};
