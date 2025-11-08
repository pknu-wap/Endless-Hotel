// Copyright by 2025-2 WAP Game 2 team


#include "Character/AI/PatrolRouteComponent.h"

// Sets default values for this component's properties
UPatrolRouteComponent::UPatrolRouteComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}



const TArray<AActor*>& UPatrolRouteComponent::GetPatrolPoints() const
{
	return reinterpret_cast<const TArray<AActor*>&>(PatrolPoints);
}

AActor* UPatrolRouteComponent::PickRandomPoint(int32& InOutIndex) const
{
	TArray<int32> ValidIndex;
	for (int32 i = 0; i < PatrolPoints.Num(); ++i)
	{
		if (IsValid(PatrolPoints[i]))
		{
			if (!(bAvoidImmediateRepeat && i == InOutIndex))
				ValidIndex.Add(i);
		}
	}
	if (ValidIndex.Num() == 0)
		return nullptr;

	const int32 ChosenIndex = ValidIndex[FMath::RandRange(0, ValidIndex.Num() - 1)];
	InOutIndex = ChosenIndex;
	return PatrolPoints[ChosenIndex].Get();
}
