// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Anomaly/Event/Anomaly_Event.h"
#include "GameSystem/SubSystem/GameSystem.h"
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

    bSolved = true;
    OriginalTransform = GetActorTransform();
    if (UGameInstance* GI = GetGameInstance())
    {
        if (UGameSystem* Sub = GI->GetSubsystem<UGameSystem>())
        {
            Sub->FloorChange_Reset.AddUniqueDynamic(this, &ThisClass::Reset);
        }
    }
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
    if(!IsValid(Sub->CurrentAnomaly) || !Sub->CurrentAnomaly->TargetAnomalyObjects.Contains(this))
    {
        bSolved = true;
    }

    SetActorTransform(OriginalTransform);

    Component_Interact->RestoreInteract();

    Object->SetSimulatePhysics(false);
    Object->SetEnableGravity(false);
    Object->SetPhysicsLinearVelocity(FVector::ZeroVector);
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

void AAnomaly_Object_Base::AllowNextInteract()
{
    if (IsValid(Component_Interact))
    {
        Component_Interact->RestoreInteract();
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

    FLatentActionInfo LatentInfo;
    LatentInfo.UUID = __LINE__;
    LatentInfo.CallbackTarget = this;

    UKismetSystemLibrary::MoveComponentTo(Object, OriginalTransform.GetLocation(), OriginalTransform.Rotator(), true, true, RestoreDuration, true, EMoveComponentAction::Move, LatentInfo);
}

#pragma endregion