// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/FootStep/Anomaly_FootStep.h"
#include "Player/AnimInstance/EHPlayerAnimInstance.h"
#include <GameFramework/Character.h>
#include <Kismet/GameplayStatics.h>
#include <Components/SkeletalMeshComponent.h>

#pragma region Activity

void AAnomaly_FootStep::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyID)
	{
	case EAnomalyID::FootStep:
		SetupAnomalyAction<ThisClass>(&ThisClass::ChangeFootStep, FAnomalyActionInfo(), true);
		ScheduleAnomaly(20);
		break;
	}
}

void AAnomaly_FootStep::DisableAnomaly()
{
	Super::DisableAnomaly();

	ChangeFootStep(false);
}

void AAnomaly_FootStep::StartAnomalyAction()
{
	ChangeFootStep(true);
}

#pragma endregion

#pragma region FootStep

void AAnomaly_FootStep::ChangeFootStep(bool bIsStart)
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto* SkeletalMesh = Player->GetMesh();
	auto* AnimInstance = Cast<UEHPlayerAnimInstance>(SkeletalMesh->GetAnimInstance());

	AnimInstance->bIsAnomalyGenerated = bIsStart;
}
#pragma endregion