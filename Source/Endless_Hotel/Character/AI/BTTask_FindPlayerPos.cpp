// Copyright by 2025-2 WAP Game 2 team

#include "BTTask_FindPlayerPos.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Character/AI/MazeMonsterController.h"

UBTTask_FindPlayerPos::UBTTask_FindPlayerPos()
{
	NodeName = TEXT("FindPlayerPos");
}

EBTNodeResult::Type UBTTask_FindPlayerPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Succeeded;
}
