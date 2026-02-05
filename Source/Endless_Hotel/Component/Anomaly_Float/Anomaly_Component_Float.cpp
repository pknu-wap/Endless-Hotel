// Copyright by 2025-2 WAP Game 2 team


#include "Component/Anomaly_Float/Anomaly_Component_Float.h"

#pragma region Base

UAnomaly_Component_Float::UAnomaly_Component_Float(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PrimaryComponentTick.bCanEverTick = false;
    bIsFloating = false;
}

void UAnomaly_Component_Float::BeginPlay()
{
    Super::BeginPlay();

    AActor* Owner = GetOwner();
    if (Owner)
    {
        TargetMesh = Cast<UPrimitiveComponent>(Owner->GetRootComponent());
    }
}

#pragma endregion

#pragma region Float

void UAnomaly_Component_Float::StartFloating()
{
    if (bIsFloating || !TargetMesh) return;

    bIsFloating = true;

    TargetMesh->SetSimulatePhysics(false);
    TargetMesh->SetEnableGravity(false);
    TargetMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);

    FloatVelocity = FVector(FMath::RandRange(-10.f, 10.f), FMath::RandRange(-10.f, 10.f), FMath::RandRange(20.f, 40.f));
    RotationVelocity = FRotator(FMath::RandRange(-30.f, 30.f), FMath::RandRange(-30.f, 30.f), FMath::RandRange(-30.f, 30.f));

    GetWorld()->GetTimerManager().SetTimer(FloatTickTimer, this, &UAnomaly_Component_Float::FloatTick, TickInterval, true);

    GetWorld()->GetTimerManager().SetTimer(StopFloatTimer, this, &UAnomaly_Component_Float::StopFloating, 10.0f, false);
}

void UAnomaly_Component_Float::FloatTick()
{
    if (!bIsFloating || !TargetMesh) return;

    AActor* Owner = GetOwner();
    if (Owner)
    {
        Owner->AddActorWorldOffset(FloatVelocity * TickInterval, true);
        Owner->AddActorWorldRotation(RotationVelocity * TickInterval);
    }
}

void UAnomaly_Component_Float::StopFloating()
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

        GetWorld()->GetTimerManager().SetTimer(FreezeTimerHandle, this, &UAnomaly_Component_Float::FreezePhysics, 2.f, false);
    }
}

void UAnomaly_Component_Float::FreezePhysics()
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

