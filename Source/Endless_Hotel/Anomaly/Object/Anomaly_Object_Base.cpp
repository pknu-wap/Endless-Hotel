// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Anomaly/Event/Anomaly_Event.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>

#pragma region Base

void AAnomaly_Object_Base::BeginPlay()
{
	Super::BeginPlay();

    bSolved = true;
    SaveOriginalTransform();
    auto* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();
    Sub->RegisterAnomalyObject(this);
    Sub->FloorChange_Reset.AddUniqueDynamic(this, &ThisClass::Reset);
}

void AAnomaly_Object_Base::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    auto* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();
    Sub->UnRegisterAnomalyObject(this);

    Super::EndPlay(EndPlayReason);
}

void AAnomaly_Object_Base::Reset()
{
    auto* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();
    if(!Sub->CurrentAnomaly->TargetAnomalyObjects.Contains(this))
    {
        bSolved = true;
    }
    SetActorTransform(OriginalTransform);
    Component_Interact->RestoreInteract();
}

#pragma endregion

#pragma region Interact

void AAnomaly_Object_Base::Interact_Implementation(AEHCharacter* Interacter)
{
    FInteractInfo Info = Component_Interact->GetSelectedInteractInfo();
    if (bIsOrderedInteractTypes)
    {
        if (CorrectInteractTypes[0] == Info.InteractType)
        {
            CorrectInteractTypes.Remove(Info.InteractType);
            if (CorrectInteractTypes.Num() == 0)
            {
                bSolved = !bSolved;
            }
            Component_Interact->RestoreInteract();
        }
        else
        {
            bSolved = false;
        }
    }
    else
    {
        if (CorrectInteractTypes.Contains(Info.InteractType))
        {
            bSolved = !bSolved;
        }
        else
        {
            bSolved = false;
        }
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