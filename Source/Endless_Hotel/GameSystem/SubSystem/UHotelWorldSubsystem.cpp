// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/SubSystem/UHotelWorldSubsystem.h"
#include "AnomalyProgressSubSystem.h"
#include "Anomaly/Base/Anomaly_Base_Neapolitan.h"
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

	AActor* FoundActor = UGameplayStatics::GetActorOfClass(&InWorld, AAnomaly_Base_Neapolitan::StaticClass());
	AAnomaly_Base_Neapolitan* AnomalyActor = Cast<AAnomaly_Base_Neapolitan>(FoundActor);
	
	if (!AnomalyActor) return;
	FVector TargetPos = AnomalyActor->GetAnomalyStartPos();
	Player->SetActorLocation(TargetPos);
}
