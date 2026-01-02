// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/ShelfDoll/Anomaly_Object_ShelfDoll.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

#pragma region Base

AAnomaly_Object_ShelfDoll::AAnomaly_Object_ShelfDoll(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SM_Doll = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Doll"));
	SM_Doll->SetupAttachment(RootComponent);

	SM_Doll->SetVisibility(false);
	SM_Doll->SetHiddenInGame(true);
}

#pragma endregion

#pragma region Doll

void AAnomaly_Object_ShelfDoll::ActivateDoll_Show()
{
	if (!SM_Doll)
	{
		return;
	}

	SM_Doll->SetVisibility(true);
	SM_Doll->SetHiddenInGame(false);
}

#pragma endregion

#pragma region ShelfBook

void AAnomaly_Object_ShelfDoll::ActivateShelfBook_Hide()
{
	if (!BP_ShelfBookActor)
	{
		return;
	}
	BP_ShelfBookActor->SetActorHiddenInGame(true);
}

#pragma endregion

#pragma region Plant

void AAnomaly_Object_ShelfDoll::ActivatePlant_Hide()
{
	if (!BP_PlantBeforeActor)
	{
		return;
	}
	BP_PlantBeforeActor->SetActorHiddenInGame(true);
}

#pragma endregion
