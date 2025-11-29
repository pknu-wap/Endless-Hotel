// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/EightExit/FootStep/Anomaly_FootStep.h"
#include "Player/AnimInstance/EHPlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"

void AAnomaly_FootStep::ActivateAnomaly(uint8 Anomaly_ID)
{
    Super::ActivateAnomaly(Anomaly_ID);

    switch (Anomaly_ID) {
    case 15:
        FootStep();
        break;
    }
}

void AAnomaly_FootStep::FootStep()
{
    // 1) 플레이어 가져오기
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!Player) return;

    // 2) 메시 가져오기
    USkeletalMeshComponent* Mesh = Player->GetMesh();
    if (!Mesh) return;

    // 3) AnimInstance 가져오기
    UEHPlayerAnimInstance* Anim = Cast<UEHPlayerAnimInstance>(Mesh->GetAnimInstance());
    if (!Anim) return;

    // 4) AnimBP의 bool 값 변경
    Anim->bIsAnomalyGenerated = true;

    UE_LOG(LogTemp, Warning, TEXT("Footstep anomaly generated: bIsAnomalyGenerated = true"));
}