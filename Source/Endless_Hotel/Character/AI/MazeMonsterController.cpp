// Copyright by 2025-2 WAP Game 2 team


#include "Character/AI/MazeMonsterController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionSystem.h"

#pragma region Key

const FName AMazeMonsterController::Key_TargetPlayer = TEXT("TargetPlayer");
const FName AMazeMonsterController::Key_LastKnownPos = TEXT("LastKnownPos");
const FName AMazeMonsterController::Key_PatrolPos = TEXT("PatrolPos");

#pragma endregion

#pragma region Base

AMazeMonsterController::AMazeMonsterController()
{
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	SightConfig->SightRadius = 800.f;
	SightConfig->LoseSightRadius = 900.f;
	SightConfig->PeripheralVisionAngleDegrees = 120.f;
	SightConfig->SetMaxAge(2.f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	Perception->ConfigureSense(*SightConfig);
	Perception->SetDominantSense(SightConfig->GetSenseImplementation());
	SetPerceptionComponent(*Perception);
}

void AMazeMonsterController::BeginPlay()
{
	Super::BeginPlay();
	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &AMazeMonsterController::OnTargetDetected);
}

#pragma endregion

void AMazeMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* RawBB = nullptr;
	if (UseBlackboard(BBAsset, RawBB))
	{
		RunBehaviorTree(BTAsset);
	}
}

void AMazeMonsterController::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Blackboard) return;

	if (Stimulus.WasSuccessfullySensed())
	{
		Blackboard->SetValueAsObject(Key_TargetPlayer, Actor);
		Blackboard->SetValueAsVector(Key_LastKnownPos, Actor->GetActorLocation());
	}
	else
	{
		AActor* LastSeen = Cast<AActor>(Blackboard->GetValueAsObject(Key_TargetPlayer));
		if (LastSeen)
			Blackboard->SetValueAsVector(Key_LastKnownPos, LastSeen->GetActorLocation());
		Blackboard->ClearValue(Key_TargetPlayer);
	}
}