// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/Neapolitan/SignDrop/Anomaly_Object_SignDrop.h"
#include "Component/Interact/InteractComponent.h"
#include "Actor/RoomSign/RoomSignActor.h"
#include "Player/Controller/EHPlayerController.h"
#include <Kismet/GameplayStatics.h>

#pragma region Drop

void AAnomaly_Object_SignDrop::AttachSignToMe(AActor* TargetActor)
{
    if (TargetActor)
    {
        UPrimitiveComponent* RootPrim = Cast<UPrimitiveComponent>(TargetActor->GetRootComponent());
        if (RootPrim)
        {
            RootPrim->SetSimulatePhysics(false);
        }


        FAttachmentTransformRules AttachRules(
            EAttachmentRule::KeepWorld,
            EAttachmentRule::KeepWorld,
            EAttachmentRule::KeepWorld,
            false
        );

        TargetActor->AttachToComponent(this->GetRootComponent(), AttachRules);
    }
}

void AAnomaly_Object_SignDrop::ExecuteSignDrop()
{
    bSolved = false;
    if (RoomSigns.Num() == 0) return;

    int32 RandomIndex = FMath::RandRange(0, RoomSigns.Num() - 1);
    ARoomSignActor* TargetSign = RoomSigns[RandomIndex];

    if (!TargetSign) return;

    OriginalTransform = TargetSign->OriginalTransform;

    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        PC->ClientStartCameraShake(CameraShakeClass, 0.3f);
    }
    TargetSign->DropSign();


    FTimerHandle AttachTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(AttachTimerHandle, FTimerDelegate::CreateWeakLambda(this, [this, TargetSign]()
        {
            if (!IsValid(this) || !IsValid(TargetSign)) return;
            SetActorLocationAndRotation(TargetSign->GetActorLocation(), TargetSign->GetActorRotation());
            AttachSignToMe(TargetSign);
        }), 1.0f, false);

    RoomSigns.RemoveAt(RandomIndex);
}

#pragma endregion

#pragma region Interact

void AAnomaly_Object_SignDrop::OnSignRestored()
{
    bSolved = true;
}

#pragma endregion