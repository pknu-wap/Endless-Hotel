// Copyright by 2025-2 WAP Game 2 team


#include "Player/AnimInstance/EHPlayerAnimInstance.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/Controller/EHPlayerController.h"

void UEHPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);


    APawn* OwnerPawn = TryGetPawnOwner();
    if (!OwnerPawn)
    {
        return;
    }

    FVector Velocity = OwnerPawn->GetVelocity();
    Velocity.Z = 0.f;
    ActualSpeed = Velocity.Size();


    const float StopThreshold = 5.0f;
    if (ActualSpeed < StopThreshold)
    {
        TargetSpeed = 0.f;
    }
    else
    {
        TargetSpeed = ActualSpeed;
    }

    if (AController* Controller = OwnerPawn->GetController())
    {
        if (AEHPlayerController* EHPC = Cast<AEHPlayerController>(Controller))
        {

            bIsRunningState = EHPC->GetIsRunning();
            bIsCrouchingState = EHPC->GetIsCrouching();
            bIsFaceCoveringState = EHPC->GetIsFaceCovering();
        }
    }

    const float InterpSpeedValue = 20.0f;
    const float InterpedSpeed =
        FMath::FInterpTo(ActualSpeed, TargetSpeed, DeltaSeconds, InterpSpeedValue);

    if (bIsRunningState)
    {
        Speed = InterpedSpeed * RunSpeedMultiplier;
    }
    else
    {
        Speed = InterpedSpeed;
    }

}