// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/Neapolitan/Doll/Anomaly_Object_Doll.h"
#include <Niagara/Public/NiagaraComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Kismet/GameplayStatics.h>

#pragma region Base

AAnomaly_Object_Doll::AAnomaly_Object_Doll(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Object->SetVisibility(false);

	Niagara_Fire = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara_Fire"));
	Niagara_Fire->SetupAttachment(Object);
	Niagara_Fire->SetAutoActivate(false);

	bSolved = false;
}

#pragma endregion

#pragma region Doll

void AAnomaly_Object_Doll::ActivateDoll_Show()
{
	Object->SetVisibility(true);
	Object->SetHiddenInGame(false);
}

#pragma endregion

#pragma region Interact

void AAnomaly_Object_Doll::Interact_Implementation()
{
	Super::Interact_Implementation();

	FInteractInfo Info = Component_Interact->GetSelectedInteractInfo();

	switch (Info.InteractType)
	{
	case EInteractType::Burn:
		InteractFire();
		break;
	}
}

void AAnomaly_Object_Doll::InteractFire()
{
	InteractedMoveStep(0);
	bSolved = !bSolved;
}

void AAnomaly_Object_Doll::InteractedMoveStep(int32 step)
{
	FTimerHandle InteractHandle;
	GetWorld()->GetTimerManager().SetTimer(InteractHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			Niagara_Fire->SetActive(true, true);
		}), 1.f, false);
}