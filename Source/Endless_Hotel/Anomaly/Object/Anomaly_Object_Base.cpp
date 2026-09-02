// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Anomaly/Event/Anomaly_Event.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include "GameSystem/SubSystem/AnomalyPoolSubsystem.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include "Component/Float/FloatComponent.h"
#include <Kismet/KismetSystemLibrary.h>

#pragma region Base

AAnomaly_Object_Base::AAnomaly_Object_Base(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{

#if WITH_EDITORONLY_DATA

    SetIsSpatiallyLoaded(false);

#endif

}

void AAnomaly_Object_Base::BeginPlay()
{
    Super::BeginPlay();

    OriginalTransform = GetActorTransform();
    
    auto* FloorSub = GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>();
    auto* AnomalySub = GetGameInstance()->GetSubsystem<UAnomalyPoolSubsystem>();
    ResetHandle = FloorSub->FloorChange_Reset.AddUObject(this, &ThisClass::Reset);
    AnomalySub->RegisterAnomalyObject(this);
}

void AAnomaly_Object_Base::EndPlay(EEndPlayReason::Type EndPlayReason)
{
    auto* FloorSub = GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>();
    FloorSub->FloorChange_Reset.Remove(ResetHandle);

    SetActorTransform(OriginalTransform);

    Super::EndPlay(EndPlayReason);
}

#pragma endregion

#pragma region Reset

void AAnomaly_Object_Base::Reset()
{
    if (!OwnerAnomalyEvent.IsValid())
    {
        bSolved = true;
    }

    SetActorTransform(OriginalTransform);

    Component_Interact->ActiveInteract(true);

    Object->SetSimulatePhysics(false);
    Object->SetEnableGravity(false);
    Object->SetPhysicsLinearVelocity(FVector::ZeroVector);

    for (auto* Target : GetComponentsByTag(UStaticMeshComponent::StaticClass(), TEXT("Float")))
    {
        auto* Mesh = Cast<UStaticMeshComponent>(Target);
        Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
    }
}

void AAnomaly_Object_Base::SetOwnerAnomalyEvent(AAnomaly_Event* NewEvent)
{
    OwnerAnomalyEvent = NewEvent;
}

#pragma endregion

#pragma region Interact

void AAnomaly_Object_Base::Interact(AEHCharacter* Interacter)
{
    FInteractInfo Info = Component_Interact->GetSelectedInteractInfo();
    auto* VerdictSub = GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();
    const bool bIsAnomalyTarget = IsValid(VerdictSub) && IsValid(VerdictSub->CurrentAnomaly) && VerdictSub->CurrentAnomaly->TargetAnomalyObjects.Contains(this);
    if (!bIsAnomalyTarget)
    {
        bSolved = false;
        if (IsValid(VerdictSub))
        {
            VerdictSub->bWrongInteractionOccurred = true;
        }
    }
    else if (bIsOrderedInteractTypes)
    {
        if (CorrectInteractTypes[0] == Info.InteractType)
        {
            CorrectInteractTypes.Remove(Info.InteractType);
            if (CorrectInteractTypes.Num() == 0)
            {
                bSolved = !bSolved;
            }
            Component_Interact->ActiveInteract(true);
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

void AAnomaly_Object_Base::AllowNextInteract()
{
    if (IsValid(Component_Interact))
    {
        Component_Interact->ActiveInteract(true);
    }
}

#pragma endregion

#pragma region Floating

void AAnomaly_Object_Base::StartFloating()
{
    auto* Comp_Float = FindComponentByClass<UFloatComponent>();
    if (!IsValid(Comp_Float))
    {
        return;
    }

    constexpr float StartDuration = 2.5f;
    FTimerHandle StartHandle;
    GetWorld()->GetTimerManager().SetTimer(StartHandle, FTimerDelegate::CreateWeakLambda(this, [this, Comp_Float]
        {
            Comp_Float->StartFloating();
        }), StartDuration, false);
}

#pragma endregion

#pragma region Restore

void AAnomaly_Object_Base::StartRestoring(float Duration)
{
    constexpr float RestoreDuration = 1.0f;

    Object->SetSimulatePhysics(false);
    Object->SetEnableGravity(false);
    Object->SetPhysicsLinearVelocity(FVector::ZeroVector);
    
    for (auto* Target : GetComponentsByTag(UStaticMeshComponent::StaticClass(), TEXT("Float")))
    {
        auto* Mesh = Cast<UStaticMeshComponent>(Target);
        Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
    }

    FLatentActionInfo LatentInfo;
    LatentInfo.UUID = __LINE__;
    LatentInfo.CallbackTarget = this;

    UKismetSystemLibrary::MoveComponentTo(Object, OriginalTransform.GetLocation(), OriginalTransform.Rotator(), true, true, RestoreDuration, true, EMoveComponentAction::Move, LatentInfo);
}

#pragma endregion