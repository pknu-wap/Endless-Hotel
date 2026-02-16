// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/FootStep/Anomaly_Object_FootStep.h"
#include "Player/AnimInstance/EHPlayerAnimInstance.h"
#include <GameFramework/Character.h>
#include <Kismet/GameplayStatics.h>
#include <Components/SkeletalMeshComponent.h>

#pragma region Activity

void AAnomaly_Object_FootStep::ChangeFootStep()
{
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    USkeletalMeshComponent* Mesh = Player->GetMesh();
    UEHPlayerAnimInstance* Anim = Cast<UEHPlayerAnimInstance>(Mesh->GetAnimInstance());

    Anim->bIsAnomalyGenerated = true;
}

#pragma endregion