// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Anomaly_Object_Base.h"
#include <Components/WidgetComponent.h>

#pragma region Base

void AAnomaly_Object_Base::BeginPlay()
{
	Super::BeginPlay();

    bSolved = true;
    SaveOriginalTransform();
}

#pragma endregion

#pragma region Interact

void AAnomaly_Object_Base::Interact_Implementation(AEHCharacter* Interacter)
{
    FInteractInfo Info = Component_Interact->GetSelectedInteractInfo();

    if (Info.InteractType == CorrectInteractType)
    {
        bSolved = !bSolved;
    }
    else
    {
        bSolved = false;
    }

    switch (Info.InteractType)
    {
    case EInteractType::Restore:
        StartRestoring();
        break;
    }
}

#pragma endregion

#pragma region Restore

void AAnomaly_Object_Base::SaveOriginalTransform()
{
    OriginalTransform = GetActorTransform();
}

void AAnomaly_Object_Base::StartRestoring(float Duration)
{
    GetWorld()->GetTimerManager().ClearTimer(RestoreHandle);

    RestoreDuration = FMath::Max(Duration, 0.01f);
    RestoreCurrentTime = 0.f;

    GetWorld()->GetTimerManager().SetTimer(RestoreHandle, this, &ThisClass::RestoreTick, 0.01f, true);
}

void AAnomaly_Object_Base::RestoreTick()
{
    RestoreCurrentTime += GetWorld()->GetDeltaSeconds();
    float RawAlpha = FMath::Clamp(RestoreCurrentTime / RestoreDuration, 0.f, 1.f);
    float Alpha = FMath::InterpEaseInOut(0.f, 1.f, RawAlpha, 2.f);

    FTransform CurrentTransform = GetActorTransform();
    FTransform NewTransform;
    NewTransform.Blend(CurrentTransform, OriginalTransform, Alpha);
    SetActorTransform(NewTransform);

    if (RawAlpha >= 1.0f)
    {
        FinishRestoring();
    }
}

void AAnomaly_Object_Base::FinishRestoring()
{
    GetWorld()->GetTimerManager().ClearTimer(RestoreHandle);

    SetActorTransform(OriginalTransform);

    if (UPrimitiveComponent* RootPrim = Cast<UPrimitiveComponent>(GetRootComponent()))
    {
        RootPrim->SetSimulatePhysics(false);
    }
}

#pragma endregion