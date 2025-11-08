// Copyright by 2025-2 WAP Game 2 team

#include "Character/AI/BTService_Detect.h"
#include "Character/AI/MazeMonsterController.h"
#include "Player/Character/EHPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"


UBTServiece_Detect::UBTServiece_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTServiece_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) return;

	UWorld* World = ControllingPawn->GetWorld();
	if (World == nullptr) return;

	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 600.f;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);

	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			AEHPlayer* EHPlayer = Cast<AEHPlayer>(OverlapResult.GetActor());
			if (EHPlayer)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMazeMonsterController::Key_TargetPlayer, EHPlayer);
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, Interval);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), EHPlayer->GetActorLocation(), FColor::Blue, false, 0.2f);
				return;
			}
		}
	}
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, Interval);
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMazeMonsterController::Key_TargetPlayer, nullptr);
}