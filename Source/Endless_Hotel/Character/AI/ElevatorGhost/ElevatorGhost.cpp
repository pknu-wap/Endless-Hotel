// Copyright by 2026-1 WAP Game 2 team

#include "Character/AI/ElevatorGhost/ElevatorGhost.h"
#include "Character/AI/ElevatorGhost/ElevatorGhostAnimInstance.h"
#include "Player/Character/EHPlayer.h"
#include "Player/Controller/EHPlayerController.h"
#include "Type/Player/Type_Death.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>

#pragma region Base

AElevatorGhost::AElevatorGhost(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
    EyeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EyeMesh"));
    EyeMesh->SetupAttachment(GetMesh(), TEXT("EyeSocket"));
    EyeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AElevatorGhost::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bShouldLookAtPlayer)
    {
        UpdateLookAtPlayer(DeltaTime);
    }

    AEHPlayer* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    AEHPlayerController* PC = Cast<AEHPlayerController>(Player->GetController());
    if (PC && !PC->bIsFaceCovering)
    {
        AttackPlayer();
        SetActorTickEnabled(false);
    }
}

#pragma endregion

#pragma region Look

void AElevatorGhost::UpdateLookAtPlayer(float DeltaTime)
{
    AEHPlayer* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (!Player)
    {
        return;
    }

    FRotator TargetRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Player->GetActorLocation());
    TargetRot.Pitch = 0.f;
    TargetRot.Roll = 0.f;

    FRotator NewRot = FMath::RInterpTo(GetActorRotation(), TargetRot, DeltaTime, TurnInterpSpeed);
    SetActorRotation(NewRot);
}

#pragma endregion

#pragma region Attack

void AElevatorGhost::AttackPlayer()
{
    AEHPlayer* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    AEHPlayerController* PC = Cast<AEHPlayerController>(Player->GetController());
    
    SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Player->GetActorLocation()));

    PC->SetPlayerInputAble(false);
    if (auto* AnimInst = Cast<UElevatorGhostAnimInstance>(GetMesh()->GetAnimInstance()))
    {
        AnimInst->bIsAttacking = true;
        Player->DieDelegate.Broadcast(EDeathReason::Attack);
        bShouldLookAtPlayer = false;
    }
}

#pragma endregion