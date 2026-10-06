// Copyright by 2026-1 WAP Game 2 team

#include "Component/Elevator/ElevatorPassengerComponent.h"
#include "GameSystem/SubSystem/ElevatorManagerSubsystem.h"
#include <Components/PrimitiveComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Camera/PlayerCameraManager.h>
#include <GameFramework/Character.h>
#include <GameFramework/PlayerController.h>
#include <GameFramework/CharacterMovementComponent.h>

#pragma region Base

void UElevatorPassengerComponent::Init(USceneComponent* InAnchor, UPrimitiveComponent* InExterior, UPrimitiveComponent* InCar)
{
    Anchor = InAnchor;
    Exterior = InExterior;
    Car = InCar;
}

void UElevatorPassengerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(CollisionRestoreHandle);
    }
    Super::EndPlay(EndPlayReason);
}

#pragma endregion

#pragma region Passenger

FElevatorPassengerSnapshot UElevatorPassengerComponent::Capture() const
{
    FElevatorPassengerSnapshot Snap;
    const ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!Player || !Anchor)
    {
        return Snap;
    }

    const FTransform AnchorTM = Anchor->GetComponentTransform();
    Snap.LocalLocation = AnchorTM.InverseTransformPosition(Player->GetActorLocation());
    const AController* PC = Player->GetController();
    Snap.LocalControlRotation = AnchorTM.InverseTransformRotation(PC->GetControlRotation().Quaternion());
    const UCharacterMovementComponent* CMC = Player->GetCharacterMovement();
    Snap.LocalVelocity = AnchorTM.InverseTransformVectorNoScale(CMC->Velocity);
    Snap.MovementMode = CMC->MovementMode;

    Snap.bIsValid = true;
    return Snap;
}

void UElevatorPassengerComponent::Restore(const FElevatorPassengerSnapshot& Snap)
{
    if (!Snap.bIsValid || !Anchor)
    {
        return;
    }

    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    APlayerController* PC = Player ? Cast<APlayerController>(Player->GetController()) : nullptr;
    UCharacterMovementComponent* CMC = Player ? Player->GetCharacterMovement() : nullptr;
    if (!PC || !CMC)
    {
        return;
    }

    const FTransform AnchorTM = Anchor->GetComponentTransform();
    const FVector NewLocation = AnchorTM.TransformPosition(Snap.LocalLocation);
    const FRotator NewControlRot = AnchorTM.TransformRotation(Snap.LocalControlRotation).Rotator();
    const FVector NewVelocity = AnchorTM.TransformVectorNoScale(Snap.LocalVelocity);

    if (bDisableCollisionOnRestore)
    {
        SetElevatorCollision(false);
    }

    Player->SetActorLocationAndRotation(NewLocation, FRotator(0.f, NewControlRot.Yaw, 0.f), false, nullptr, ETeleportType::TeleportPhysics);
    PC->SetControlRotation(NewControlRot);
    if (PC->PlayerCameraManager)
    {
        PC->PlayerCameraManager->SetGameCameraCutThisFrame();
    }

    Player->SetBase(nullptr);
    Player->SetActorEnableCollision(true);
    CMC->Velocity = NewVelocity;
    CMC->SetMovementMode(bDisableCollisionOnRestore ? MOVE_Falling : Snap.MovementMode.GetValue());

    if (bDisableCollisionOnRestore)
    {
        GetWorld()->GetTimerManager().SetTimer(CollisionRestoreHandle,FTimerDelegate::CreateWeakLambda(this, [this]()
        {
            SetElevatorCollision(true);
        }), CollisionRestoreDelay, false);
    }
}

void UElevatorPassengerComponent::CancelRestore()
{
    FTimerManager& TimerManager = GetWorld()->GetTimerManager();
    if (TimerManager.IsTimerActive(CollisionRestoreHandle))
    {
        TimerManager.ClearTimer(CollisionRestoreHandle);
        SetElevatorCollision(true);
    }
}

void UElevatorPassengerComponent::SetElevatorCollision(bool bEnable)
{
    const ECollisionEnabled::Type Mode = bEnable ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision;
    if (Exterior)
    {
        Exterior->SetCollisionEnabled(Mode);
    }
    if (Car)
    {
        Car->SetCollisionEnabled(Mode);
    }
}

#pragma endregion