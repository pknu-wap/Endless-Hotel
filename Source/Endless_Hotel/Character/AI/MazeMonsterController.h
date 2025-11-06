// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MazeMonsterController.generated.h"

#pragma region Declare
	
	class UAIPerceptionComponent;
	class UAISenseConfig_Sight;
	class UBehaviorTree;
	class UBlackboardData;
	class UBlackboardComponent;
	
	struct FPathFollowingResult;

#pragma endregion


UCLASS()
class ENDLESS_HOTEL_API AMazeMonsterController : public AAIController
{
	GENERATED_BODY()

#pragma region Base

public:
	AMazeMonsterController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

#pragma endregion

#pragma region Setting

protected:
	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = "AI|Perception")
	TObjectPtr<UAIPerceptionComponent> AIPerception = nullptr;

	UPROPERTY()
	TObjectPtr<UAISenseConfig_Sight> SightConfig = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BTAsset = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBlackboardData> BBAsset = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	UBlackboardComponent* BBComponent = nullptr;

#pragma endregion

#pragma region Search & Move

	UFUNCTION()
	void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);

#pragma endregion

#pragma region Key

public:
	static const FName Key_TargetPlayer;
	static const FName Key_LastKnownPos;
	static const FName Key_SpawnLocation;

#pragma endregion

};
