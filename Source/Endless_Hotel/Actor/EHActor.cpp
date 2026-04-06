// Copyright by 2025-2 WAP Game 2 team

#include "Actor/EHActor.h"

#pragma region Base

AEHActor::AEHActor(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEHActor::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

	Super::EndPlay(EndPlayReason);
}

#pragma endregion