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
    if (!CachedPawnOwner)
    {
        CachedPawnOwner = TryGetPawnOwner();
        if (!CachedPawnOwner) return;
    }

    FVector Velocity = CachedPawnOwner->GetVelocity();
    Velocity.Z = 0.f;
    ActualSpeed = Velocity.Size();

    FRotator ActorRotation = CachedPawnOwner->GetActorRotation();
    FVector LocalVelocity = ActorRotation.UnrotateVector(Velocity);
    ActualSpeed_X = LocalVelocity.X;
    ActualSpeed_Y = LocalVelocity.Y;

    if (ActualSpeed < StopThreshold)
    {
        TargetSpeed = 0.f;
        TargetSpeed_X = 0.f;
        TargetSpeed_Y = 0.f;
    }

    else
    {
        TargetSpeed = ActualSpeed;
        TargetSpeed_X = ActualSpeed_X;
        TargetSpeed_Y = ActualSpeed_Y;
    }

    if (AController* Controller = CachedPawnOwner->GetController())
    {
        if (AEHPlayerController* EHPC = Cast<AEHPlayerController>(Controller))
        {
            bIsRunningState = EHPC->GetIsRunning();
            bIsCrouchingState = EHPC->GetIsCrouching();
            bIsFaceCoveringState = EHPC->GetIsFaceCovering();
        }
    }
    const float InterpedSpeed = FMath::FInterpTo(ActualSpeed, TargetSpeed, DeltaSeconds, InterpSpeedValue);
    const float InterpedSpeed_X = FMath::FInterpTo(ActualSpeed_X, TargetSpeed_X, DeltaSeconds, InterpSpeedValue);
    const float InterpedSpeed_Y = FMath::FInterpTo(ActualSpeed_Y, TargetSpeed_Y, DeltaSeconds, InterpSpeedValue);

    if (bIsRunningState)
    {
        HorizontalSpeed = InterpedSpeed_X * RunSpeedMultiplier;
        VerticalSpeed = InterpedSpeed_Y * RunSpeedMultiplier;
    }

    else
    {
        HorizontalSpeed = InterpedSpeed_X;
        VerticalSpeed = InterpedSpeed_Y;
        Speed = InterpedSpeed;
    }
}