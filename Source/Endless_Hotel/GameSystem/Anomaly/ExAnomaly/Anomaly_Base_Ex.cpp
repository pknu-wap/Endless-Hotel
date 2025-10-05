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
	
}
void AAnomaly_Base_Ex::StartAnomaly_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Anomaly %d Started"), DefaultID);
}

UAnomalyProgressSubSystem* AAnomaly_Base_Ex::SolveAnomaly()
{
	if (GetWorld())
	{

		if (UAnomalyProgressSubSystem* AnomalySubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>())
		{
			AnomalySubsystem->SetIsAnomalySolved(true);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AnomalyProgressSubSystem not found in GameInstance."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("World context is invalid."));
	}
	return nullptr;
}

UAnomalyProgressSubSystem* AAnomaly_Base_Ex::NotSolveAnomaly()
{
	if (GetWorld())
	{
		if (UAnomalyProgressSubSystem* AnomalySubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>())
		{
			AnomalySubsystem->SetIsAnomalySolved(false);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AnomalyProgressSubSystem not found in GameInstance."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("World context is invalid."));
	}
	return nullptr;
}

UAnomalyProgressSubSystem* AAnomaly_Base_Ex::VerdictAnomaly()
{
	if (GetWorld())
	{
		if (UAnomalyProgressSubSystem* AnomalySubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>())
		{
			AnomalySubsystem->AnomalyVerdict();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AnomalyProgressSubSystem not found in GameInstance."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("World context is invalid."));
	}
	return nullptr;
}