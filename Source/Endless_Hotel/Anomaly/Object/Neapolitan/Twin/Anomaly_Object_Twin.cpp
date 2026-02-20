// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/Neapolitan/Twin/Anomaly_Object_Twin.h"
#include <Components/BoxComponent.h>

#pragma region Base

AAnomaly_Object_Twin::AAnomaly_Object_Twin(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	TwinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TwinMesh"));
	RootComponent = TwinMesh;
	TwinMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAnomaly_Object_Twin::BeginPlay()
{
	Super::BeginPlay();

	SetActorHiddenInGame(true);
	SetActorLocation(FirstSpawnLocation);
}

#pragma endregion 

#pragma region Twin

void AAnomaly_Object_Twin::TwinReveal()
{
	SetActorHiddenInGame(false);
	SetActorLocation(ActiveSpawnLocation);
}

#pragma endregion
