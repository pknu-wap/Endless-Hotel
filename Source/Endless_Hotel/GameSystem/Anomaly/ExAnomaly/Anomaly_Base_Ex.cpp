// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly_Base_Ex.h"

// Sets default values
AAnomaly_Base_Ex::AAnomaly_Base_Ex(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Don't use Tick
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AAnomaly_Base_Ex::BeginPlay()
{
	Super::BeginPlay();
}

void AAnomaly_Base_Ex::StartAnomaly()
{
	UE_LOG(LogTemp, Log, TEXT("Anomaly %d Started"), DefaultID);
}
void AAnomaly_Base_Ex::StartAnomaly_Implementation()
{
	// Default implementation does nothing
}