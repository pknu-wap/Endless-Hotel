// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/EightExit/FootStep/Anomaly_Object_FootStep.h"
#include "Player/AnimInstance/EHPlayerAnimInstance.h"
#include <GameFramework/Character.h>
#include <Kismet/GameplayStatics.h>
#include <Components/SkeletalMeshComponent.h>

#pragma region Reset

void AAnomaly_Object_FootStep::Reset()
{
	Super::Reset();

    ChangeFootStep(false);
}

#pragma endregion

#pragma region FootStep

void AAnomaly_Object_FootStep::StartFootStep()
{
    ChangeFootStep(true);
}

void AAnomaly_Object_FootStep::ChangeFootStep(bool bIsStart)
{
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    USkeletalMeshComponent* Mesh = Player->GetMesh();
    UEHPlayerAnimInstance* Anim = Cast<UEHPlayerAnimInstance>(Mesh->GetAnimInstance());

    Anim->bIsAnomalyGenerated = bIsStart;
}
#pragma endregion