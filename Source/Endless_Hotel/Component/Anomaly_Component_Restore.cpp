// Copyright by 2025-2 WAP Game 2 team


#include "Component/Anomaly_Component_Restore.h"

#pragma region Base

UAnomaly_Component_Restore::UAnomaly_Component_Restore(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UAnomaly_Component_Restore::BeginPlay()
{
    Super::BeginPlay();
    SaveOriginalTransform();
}

#pragma endregion

#pragma region Restore

void UAnomaly_Component_Restore::SaveOriginalTransform()
{
    OriginalTransform = GetOwner()->GetActorTransform();
}

void UAnomaly_Component_Restore::StartRestoring(float Duration)
{
    RestoreDuration = Duration;
    RestoreCurrentTime = 0.f;

    GetWorld()->GetTimerManager().SetTimer(RestoreHandle, this, &UAnomaly_Component_Restore::RestoreTick, 0.016f, true);
}

void UAnomaly_Component_Restore::RestoreTick()
{
    AActor* Owner = GetOwner();
    if (!Owner) return;

    RestoreCurrentTime += 0.016f;
    float Alpha = FMath::Clamp(RestoreCurrentTime / RestoreDuration, 0.f, 1.f);

    FTransform CurrentTransform = Owner->GetActorTransform();
    FTransform NewTransform;
    NewTransform.Blend(CurrentTransform, OriginalTransform, Alpha);

    Owner->SetActorTransform(NewTransform);

    if (Alpha >= 1.0f)
    {
        Owner->SetActorTransform(OriginalTransform);
        GetWorld()->GetTimerManager().ClearTimer(RestoreHandle);

        if (auto* Mesh = Cast<UPrimitiveComponent>(Owner->GetRootComponent()))
        {
            Mesh->SetSimulatePhysics(false);
        }
    }
}

#pragma endregion
