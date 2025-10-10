// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly_Base_Ex.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"

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
	UE_LOG(LogTemp, Log, TEXT("[Anomaly] Anomaly ID=%d started."), DefaultID);
}

void AAnomaly_Base_Ex::SolveAnomaly()
{
	if (UAnomalyProgressSubSystem* AnomalySubsystem = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>())
	{
		AnomalySubsystem->SetIsAnomalySolved(true);
	}
}

void AAnomaly_Base_Ex::NotSolveAnomaly()
{
	if (UAnomalyProgressSubSystem* AnomalySubsystem = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>())
	{
		AnomalySubsystem->SetIsAnomalySolved(false);
	}
}

void AAnomaly_Base_Ex::VerdictAnomaly()
{
	if (UAnomalyProgressSubSystem* AnomalySubsystem = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>())
	{
		AnomalySubsystem->AnomalyVerdict();
	}
}