// Copyright by 2026-1 WAP Game 2 team

#include "Character/AI/ElevatorGhost/ElevatorGhostController.h"
#include "Character/AI/ElevatorGhost/ElevatorGhost.h"
#include "Character/AI/ElevatorGhost/ElevatorGhostAnimInstance.h"
#include "Actor/Elevator/Elevator.h"
#include <Navigation/PathFollowingComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

#pragma region Base

void AElevatorGhostController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
    ElevatorGhost = Cast<AElevatorGhost>(InPawn);
    if (ElevatorGhost.IsValid())
    {
        if (auto* MoveComp = ElevatorGhost->GetCharacterMovement())
        {
            MoveComp->RotationRate = FRotator(0.f, 240.f, 0.f);
        }
        if (auto* AnimInst = Cast<UElevatorGhostAnimInstance>(ElevatorGhost->GetMesh()->GetAnimInstance()))
        {
            AnimInst->bIsMoving = false;
        }
    }
    GetWorld()->GetTimerManager().SetTimer(MoveDelayHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
        {
            if (auto* AnimInst = Cast<UElevatorGhostAnimInstance>(ElevatorGhost->GetMesh()->GetAnimInstance()))
            {
                AnimInst->bIsMoving = true;
                StartWalkingIntoElevator();
            }
        }), WaitTime, false);
}

#pragma endregion

#pragma region Move

void AElevatorGhostController::StartWalkingIntoElevator()
{
    if (auto* AnimInst = Cast<UElevatorGhostAnimInstance>(ElevatorGhost->GetMesh()->GetAnimInstance()))
    {
        AnimInst->bIsMoving = true;
    }
    ElevatorGhost->SetActorEnableCollision(false);
    GetWorld()->GetTimerManager().SetTimer(EnterElevatorHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
        {
            if (!ElevatorGhost.IsValid()) return;

            FVector Current = ElevatorGhost->GetActorLocation();
            FVector Direction = (TargetLocation - Current).GetSafeNormal();
            FVector NewLoc = Current + Direction * WalkSpeed * GetWorld()->GetDeltaSeconds();
            ElevatorGhost->SetActorLocation(NewLoc);

            if (FVector::DistSquared(NewLoc, TargetLocation) < FMath::Square(15.f))
            {
                GetWorld()->GetTimerManager().ClearTimer(EnterElevatorHandle);
                OnGhostReachedElevator();
            }
        }), 0.016f, true);
}

void AElevatorGhostController::OnGhostReachedElevator()
{
    ElevatorGhost->SetActorRotation(TargetRotation);
    ElevatorGhost->SetActorTickEnabled(true);
    ElevatorGhost->SetActorEnableCollision(true);

    if (AElevator* Elevator = TargetElevator.Get())
    {
        Elevator->OnButtonClicked(false);
    }

    if (auto* AnimInst = Cast<UElevatorGhostAnimInstance>(ElevatorGhost->GetMesh()->GetAnimInstance()))
    {
        AnimInst->bIsMoving = false;
    }
}

#pragma endregion