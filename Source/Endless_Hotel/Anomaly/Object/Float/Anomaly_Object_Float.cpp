// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Float/Anomaly_Object_Float.h"
#include "Anomaly/Object/Anomaly_Object_Neapolitan.h"
#include "Components/WidgetComponent.h"   
#include "Component/LookAt/LookAtComponent.h"

#pragma region Base

#define LOCTEXT_NAMESPACE "Float"

AAnomaly_Object_Float::AAnomaly_Object_Float(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bIsFloating = false;
}

void AAnomaly_Object_Float::BeginPlay()
{
    Super::BeginPlay();
}

#pragma endregion

#pragma region Floating

void AAnomaly_Object_Float::StartFloating()
{
    bIsFloating = true;

    Object->SetSimulatePhysics(false);
    Object->SetEnableGravity(false);
    Object->SetPhysicsLinearVelocity(FVector::ZeroVector);

    FloatVelocity = FVector(
        FMath::RandRange(-10.f, 10.f),
        FMath::RandRange(-10.f, 10.f),
        FMath::RandRange(20.f, 40.f)
    );

    RotationVelocity = FRotator(
        FMath::RandRange(-30.f, 30.f),
        FMath::RandRange(-30.f, 30.f),
        FMath::RandRange(-30.f, 30.f)
    );

    GetWorld()->GetTimerManager().SetTimer(FloatTickTimer, FTimerDelegate::CreateWeakLambda(this, [this]()
        {
            FloatAccelerate();
        }), 0.016f, true);

    GetWorld()->GetTimerManager().SetTimer(StopFloatTimer, FTimerDelegate::CreateWeakLambda(this, [this]()
        {
            StopFloating();
        }), 10, false);
}

void AAnomaly_Object_Float::FloatAccelerate()
{
    if (!bIsFloating) return;

    const float DeltaTime = GetWorld()->GetDeltaSeconds();

    AddActorWorldOffset(FloatVelocity * DeltaTime, true);
    AddActorWorldRotation(RotationVelocity * DeltaTime);
}

void AAnomaly_Object_Float::StopFloating()
{
    if (!bIsFloating) return;

    bIsFloating = false;

    GetWorldTimerManager().ClearTimer(FloatTickTimer);
    GetWorldTimerManager().ClearTimer(StopFloatTimer);

    Object->SetSimulatePhysics(true);
    Object->SetEnableGravity(true);
}

#pragma endregion

#pragma region Restore

#pragma endregion

#pragma region Interact

//void AAnomaly_Object_Float::SetInteraction()
//{
//    InteractAction = [this]()
//        {
//            if (bIsFloating) return;
//
//            RestoreObjectTransform();
//            Object->SetSimulatePhysics(false);
//        };
//}

#pragma endregion
