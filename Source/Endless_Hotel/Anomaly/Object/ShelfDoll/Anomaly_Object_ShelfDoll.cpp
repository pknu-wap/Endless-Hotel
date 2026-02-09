// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/ShelfDoll/Anomaly_Object_ShelfDoll.h"
#include "Anomaly/Object/Plant/Anomaly_Object_Plant.h"
#include "Anomaly/Object/ShelfBook/Anomaly_Object_ShelfBook.h"
#include <Niagara/Public/NiagaraComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/Actor.h>
#include <Kismet/GameplayStatics.h>

#pragma region Base

AAnomaly_Object_ShelfDoll::AAnomaly_Object_ShelfDoll(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SM_Doll = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Doll"));
	SM_Doll->SetupAttachment(RootComponent);
	SM_Doll->SetVisibility(false);

	Niagara_Fire = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara_Fire"));
	Niagara_Fire->SetupAttachment(SM_Doll);
	Niagara_Fire->SetAutoActivate(false);

	bSolved = false;
}

#pragma endregion

#pragma region Doll

void AAnomaly_Object_ShelfDoll::ActivateDoll_Show()
{
	SM_Doll->SetVisibility(true);
	SM_Doll->SetHiddenInGame(false);

	TArray<AActor*> FoundBooks;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAnomaly_Object_ShelfBook::StaticClass(), FoundBooks);

	if (FoundBooks.Num() > 0)
	{
		for (AActor* BookActor : FoundBooks)
		{
			if (auto* ShelfBook = Cast<AAnomaly_Object_ShelfBook>(BookActor))
			{
				ShelfBook->StartBookOff();
			}
		}
	}

	TArray<AActor*> FoundPlants;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAnomaly_Object_Plant::StaticClass(), FoundPlants);

	if (FoundPlants.Num() > 0)
	{
		for (AActor* PlantActor : FoundPlants)
		{
			if (auto* Plant = Cast<AAnomaly_Object_Plant>(PlantActor))
			{
				Plant->StartPlantOff();
			}
		}
	}
}

#pragma endregion

#pragma region Interact

void AAnomaly_Object_ShelfDoll::SetInteraction()
{
	Component_Interact->AdditionalAction = ([this]()
		{
			InteractFire();
		});
}

void AAnomaly_Object_ShelfDoll::InteractFire()
{
	InteractedMoveStep(0);
	bSolved = !bSolved;
}

void AAnomaly_Object_ShelfDoll::InteractedMoveStep(int32 step)
{
	FTimerHandle InteractHandle;
	GetWorld()->GetTimerManager().SetTimer(InteractHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			Niagara_Fire->SetActive(true, true);
		}), 1.f, false);
}