// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRouteComponent.generated.h"


UCLASS(ClassGroup = (AI), meta = (BlueprintSpawnableComponent))
class ENDLESS_HOTEL_API UPatrolRouteComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Base

public:
	UPatrolRouteComponent();

#pragma endregion

#pragma region PatrolPoints

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	TArray<TObjectPtr<AActor>> PatrolPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Patrol")
	bool bAvoidImmediateRepeat = true;

public:
	UFUNCTION(BlueprintCallable, Category = "Patrol")
	const TArray<AActor*>& GetPatrolPoints() const;

	AActor* PickRandomPoint(int32& InOutIndex) const;

#pragma endregion

};