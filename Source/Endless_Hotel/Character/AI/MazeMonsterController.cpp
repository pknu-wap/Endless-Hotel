// Copyright by 2025-2 WAP Game 2 team


#include "Character/AI/MazeMonsterController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"
#include "Navigation/PathFollowingComponent.h"

const FName AMazeMonsterController::Key_TargetPlayer = TEXT("TargetPlayer");
const FName AMazeMonsterController::Key_LastKnownPos = TEXT("LastKnownPos");
const FName AMazeMonsterController::Key_SpawnLocation = TEXT("SpawnLocation");

AMazeMonsterController::AMazeMonsterController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SetPerceptionComponent(*AIPerception);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 3000.f;
	SightConfig->LoseSightRadius = 3500.f;
	SightConfig->PeripheralVisionAngleDegrees = 100.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->SetMaxAge(2.f);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 400.f;

	AIPerception->ConfigureSense(*SightConfig);
	AIPerception->SetDominantSense(*SightConfig->GetSenseImplementation());
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AMazeMonsterController::OnTargetPerceived);
}

void AMazeMonsterController::BeginPlay()
{
	Super::BeginPlay();
}

void AMazeMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BBAsset)
	{
		if (UseBlackboard(BBAsset, BBComponent))
		{
			BBComponent = GetBlackboardComponent();
			BBComponent->SetValueAsVector("SpawnLocation", InPawn->GetActorLocation());
		}
	}

	if (BTAsset)
	{
		RunBehaviorTree(BTAsset);
	}
}

void AMazeMonsterController::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{
	if (!BBComponent || !Actor) return;

	if (Stimulus.WasSuccessfullySensed())
	{
		BBComponent->SetValueAsObject(Key_TargetPlayer, Actor);
		BBComponent->SetValueAsVector(Key_LastKnownPos, Actor->GetActorLocation());
		SetFocus(Actor);
	}
	else
	{
		BBComponent->ClearValue(Key_TargetPlayer);
		BBComponent->SetValueAsVector(Key_LastKnownPos, Stimulus.StimulusLocation);
		ClearFocus(EAIFocusPriority::Gameplay);
	}
}
