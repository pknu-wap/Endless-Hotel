// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/Doll/Anomaly_Object_Doll.h"
#include "Character/AI/ComingDoll/ComingDoll.h"

#pragma region Base

AAnomaly_Object_Doll::AAnomaly_Object_Doll(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Object->SetHiddenInGame(true);
	Object->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bSolved = false;
}

#pragma endregion

#pragma region Reset

void AAnomaly_Object_Doll::InitializeOnAnomalySpawned()
{
	Super::InitializeOnAnomalySpawned();

	Object->SetHiddenInGame(true);
	Object->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	TryBurnComingDolls();
}

#pragma endregion

#pragma region Doll

void AAnomaly_Object_Doll::ActivateDoll_Show()
{
	Object->SetHiddenInGame(false);
	Object->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

#pragma endregion

#pragma region Interact

void AAnomaly_Object_Doll::Interact(AEHCharacter* Interacter)
{
	Super::Interact(Interacter);

	FInteractInfo Info = Component_Interact->GetSelectedInteractInfo();

	switch (Info.InteractType)
	{
	case EInteractType::Burn:
		TryBurnComingDolls();
		break;
	}
}

#pragma endregion

#pragma region Coming

void AAnomaly_Object_Doll::SpawnComingDolls()
{
	UWorld* World = GetWorld();

	for (FTransform Trans : SpawnTrans)
	{
		ComingDoll.Add(World->SpawnActor<AComingDoll>(ComingDollClass, Trans));
	}
}

void AAnomaly_Object_Doll::TryBurnComingDolls()
{
	if (ComingDoll.IsEmpty())
	{
		return;
	}

	for (AComingDoll* Doll : ComingDoll)
	{
		Doll->StartBurning();
	}

	ComingDoll.Empty();
}

#pragma endregion