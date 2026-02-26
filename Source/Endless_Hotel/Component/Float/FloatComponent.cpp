// Copyright by 2025-2 WAP Game 2 team


#include "Component/Float/FloatComponent.h"
#include "Component/Interact/InteractComponent.h"
#include <Kismet/GameplayStatics.h>

#pragma region Base

UFloatComponent::UFloatComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PrimaryComponentTick.bCanEverTick = false;
    bIsFloatStarted = false;
    bIsFloating = false;
}

void UFloatComponent::BeginPlay()
{
    Super::BeginPlay();

    TargetMesh = Cast<UPrimitiveComponent>(Owner->GetRootComponent());
    bIsFloatStarted = false;

    SaveOriginalTransform();
}

#pragma endregion

#pragma region Float

void UFloatComponent::StartFloating()
{
    if (bIsFloating || !TargetMesh) return;
    bIsFloatStarted = true;
    bIsFloating = true;

    TargetMesh->SetSimulatePhysics(false);
    TargetMesh->SetEnableGravity(false);
    TargetMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);

    FloatVelocity = FVector(FMath::RandRange(-10.f, 10.f), FMath::RandRange(-10.f, 10.f), FMath::RandRange(20.f, 40.f));
    RotationVelocity = FRotator(FMath::RandRange(-30.f, 30.f), FMath::RandRange(-30.f, 30.f), FMath::RandRange(-30.f, 30.f));

    GetWorld()->GetTimerManager().SetTimer(FloatTickTimer, this, &UFloatComponent::FloatTick, TickInterval, true);

    GetWorld()->GetTimerManager().SetTimer(StopFloatTimer, this, &UFloatComponent::StopFloating, 10.0f, false);
}

void UFloatComponent::FloatTick()
{
    if (!bIsFloating || !TargetMesh) return;

    Owner->AddActorWorldOffset(FloatVelocity * TickInterval, true);
    Owner->AddActorWorldRotation(RotationVelocity * TickInterval);
}

void UFloatComponent::StopFloating()
{
    if (!bIsFloating) return;

    bIsFloating = false;

    GetWorld()->GetTimerManager().ClearTimer(FloatTickTimer);
    GetWorld()->GetTimerManager().ClearTimer(StopFloatTimer);

    if (TargetMesh)
    {
        TargetMesh->SetSimulatePhysics(true);
        TargetMesh->SetEnableGravity(true);

        TargetMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);

        GetWorld()->GetTimerManager().SetTimer(FreezeTimerHandle, this, &UFloatComponent::FreezePhysics, 2.f, false);
    }
}

void UFloatComponent::FreezePhysics()
{
    GetWorld()->GetTimerManager().ClearTimer(FreezeTimerHandle);

    if (TargetMesh)
    {
        TargetMesh->SetSimulatePhysics(false);
        TargetMesh->SetEnableGravity(false);

        TargetMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
        TargetMesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
    }
}

#pragma endregion

#pragma region Restore

void UFloatComponent::SaveOriginalTransform()
{
    OriginalTransform = Owner->GetActorTransform();
}

void UFloatComponent::StartRestoring(float Duration)
{
    GetWorld()->GetTimerManager().ClearTimer(RestoreHandle);

    RestoreDuration = FMath::Max(Duration, 0.01f);
    RestoreCurrentTime = 0.f;

    GetWorld()->GetTimerManager().SetTimer(RestoreHandle, this, &UFloatComponent::RestoreTick, 0.01f, true);
}

void UFloatComponent::RestoreTick()
{
    RestoreCurrentTime += GetWorld()->GetDeltaSeconds();
    float RawAlpha = FMath::Clamp(RestoreCurrentTime / RestoreDuration, 0.f, 1.f);
    float Alpha = FMath::InterpEaseInOut(0.f, 1.f, RawAlpha, 2.f);

    FTransform CurrentTransform = Owner->GetActorTransform();
    FTransform NewTransform;
    NewTransform.Blend(CurrentTransform, OriginalTransform, Alpha);
    Owner->SetActorTransform(NewTransform);

    if (RawAlpha >= 1.0f)
    {
        FinishRestoring();
    }
}

void UFloatComponent::FinishRestoring()
{
    GetWorld()->GetTimerManager().ClearTimer(RestoreHandle);

    Owner->SetActorTransform(OriginalTransform);

    if (UPrimitiveComponent* RootPrim = Cast<UPrimitiveComponent>(Owner->GetRootComponent()))
    {
        RootPrim->SetSimulatePhysics(false);
    }

    if (OnRestored.IsBound())
    {
        OnRestored.Broadcast(Owner.Get());
    }
}

#pragma endregion

