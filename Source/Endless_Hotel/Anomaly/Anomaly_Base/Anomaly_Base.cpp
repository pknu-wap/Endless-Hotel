// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Anomaly_Base/Anomaly_Base.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"

// Sets default values
AAnomaly_Base::AAnomaly_Base(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AAnomaly_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAnomaly_Base::ActivateAnomaly_Implementation()
{
	bIsActive = true;
}

void AAnomaly_Base::IsSolveAnomaly()
{
	if (UAnomalyProgressSubSystem* AnomalySubsystem = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>())
	{
		AnomalySubsystem->SetIsAnomalySolved(true);
	}
}

void AAnomaly_Base::IsNotSolveAnomaly()
{
	if (UAnomalyProgressSubSystem* AnomalySubsystem = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>())
	{
		AnomalySubsystem->SetIsAnomalySolved(false);
	}
}

void AAnomaly_Base::IsVerdictAnomaly()
{
	if (UAnomalyProgressSubSystem* AnomalySubsystem = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>())
	{
		AnomalySubsystem->AnomalyVerdict();
	}
}