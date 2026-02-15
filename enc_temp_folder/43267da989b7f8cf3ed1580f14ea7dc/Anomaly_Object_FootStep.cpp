// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/FootStep/Anomaly_Object_FootStep.h"
#include "Player/AnimInstance/EHPlayerAnimInstance.h"
#include <GameFramework/Character.h>
#include <Kismet/GameplayStatics.h>
#include <Components/SkeletalMeshComponent.h>

#pragma region Base

AAnomaly_Object_FootStep::AAnomaly_Object_FootStep(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
}

#pragma endregion

#pragma region Activity

void AAnomaly_Object_FootStep::ChangeFootStep()
{
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!Player) return;

    USkeletalMeshComponent* Mesh = Player->GetMesh();
    if (!Mesh) return;

    UEHPlayerAnimInstance* Anim = Cast<UEHPlayerAnimInstance>(Mesh->GetAnimInstance());
    if (!Anim) return;

    Anim->bIsAnomalyGenerated = true;

    UE_LOG(LogTemp, Warning, TEXT("Footstep anomaly generated: bIsAnomalyGenerated = true"));
}

#pragma endregion