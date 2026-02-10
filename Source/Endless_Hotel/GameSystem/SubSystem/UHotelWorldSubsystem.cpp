// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/SubSystem/UHotelWorldSubsystem.h"
#include "AnomalyProgressSubSystem.h"
#include "GameSystem/Anomaly/Anomaly_Generator.h"
#include "Anomaly/Base/Anomaly_Base.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>

void UUHotelWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	UAnomalyProgressSubSystem* Progress = InWorld.GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(&InWorld, 0);
	if (!Player) return;

	if (!Progress->bPassed)
	{
		Player->SetActorLocation(PlayerStartLocation);
		return;
	}

	AAnomaly_Generator* AnomalyGenerator;
	AAnomaly_Base* AnomalyActor = Cast<AAnomaly_Base>(AnomalyGenerator->CurrentAnomaly);
	
	if (!AnomalyActor) return;
	FVector TargetPos = AnomalyActor->GetAnomalyStartPos();
	Player->SetActorLocation(TargetPos);
}
