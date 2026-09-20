// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/FootStep/Anomaly_FootStep.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>

#pragma region Activity

void AAnomaly_FootStep::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyID)
	{
	case EAnomalyID::FootStep:
		SetupAnomalyAction<ThisClass>(&ThisClass::SpawnFootStep);
		ScheduleAnomaly();
		break;
	}
}

void AAnomaly_FootStep::DisableAnomaly()
{
	GetWorld()->GetTimerManager().ClearTimer(SpawnHandle);

	Super::DisableAnomaly();
}

#pragma endregion

#pragma region FootStep

void AAnomaly_FootStep::SpawnFootStep()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	GetWorld()->GetTimerManager().SetTimer(SpawnHandle, FTimerDelegate::CreateWeakLambda(this, [this, Player]
		{
			FTransform SpawnTrans;

			FVector SpawnLoc = Player->GetActorLocation();
			constexpr float BackOffset = 50.0f;
			SpawnLoc -= Player->GetActorForwardVector() * BackOffset;
			SpawnLoc.Z = 600.f;
			SpawnTrans.SetLocation(SpawnLoc);

			SpawnTrans.SetRotation(Player->GetActorRotation().Quaternion());

			float LeftValue = bIsLeft ? 1.f : -1.f;
			SpawnTrans.SetScale3D(FVector(1, LeftValue, 1));

			if (Player->GetVelocity().SizeSquared2D() > 0.f)
			{
				GetWorld()->SpawnActor<AAnomaly_Object_FootStep>(FootStepClass, SpawnTrans);
				bIsLeft = !bIsLeft;
			}
		}), 0.3f, true);
}

#pragma endregion