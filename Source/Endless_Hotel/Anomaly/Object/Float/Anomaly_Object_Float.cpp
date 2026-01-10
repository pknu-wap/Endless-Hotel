// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Float/Anomaly_Object_Float.h"
#include "Anomaly/Object/Anomaly_Object_Neapolitan.h"
#include "UI/World/Interact/UI_Interact.h"
#include "Components/WidgetComponent.h"   
#include "Component/LookAt/LookAtComponent.h"

#pragma region Base

AAnomaly_Object_Float::AAnomaly_Object_Float(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

}

void AAnomaly_Object_Float::BeginPlay()
{
    AActor::BeginPlay();

	OriginLocation = GetActorLocation();
	OriginRotation = GetActorRotation();
}

#pragma endregion

#pragma region Floating

void AAnomaly_Object_Float::StartFloating()
{
    bIsFloating = true;

    Mesh->SetSimulatePhysics(false);
    Mesh->SetEnableGravity(false);
    Mesh->SetPhysicsLinearVelocity(FVector::ZeroVector);

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

    Mesh->SetSimulatePhysics(true);
    Mesh->SetEnableGravity(true);
}

#pragma endregion

#pragma region Restore

void AAnomaly_Object_Float::RestoreToOrigin()
{
    StopFloating();

    Mesh->SetSimulatePhysics(false);

    SetActorLocation(OriginLocation);
    SetActorRotation(OriginRotation);

    Mesh->SetSimulatePhysics(true);
}

#pragma endregion

#pragma region Interact

void AAnomaly_Object_Float::Interacted_Implementation()
{
    bSolved = true;
    RestoreToOrigin();
}

void AAnomaly_Object_Float::ShowInteractWidget_Implementation(bool bIsShow)
{
    if (!UI_Interact)
    {
        return;
    }
    UI_Interact->ShowDescription(bIsShow);
}

#pragma endregion
