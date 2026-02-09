// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/SignDrop/Anomaly_Object_SignDrop.h"
#include "Actor/RoomSign/RoomSignActor.h"
#include <Kismet/GameplayStatics.h>

#pragma region Base

AAnomaly_Object_SignDrop::AAnomaly_Object_SignDrop(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
    bSolved = false;
}

void AAnomaly_Object_SignDrop::BeginPlay()
{
	Super::BeginPlay();

    SetInteraction();
	RoomSigns.Empty();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(),
		ARoomSignActor::StaticClass(),
		FoundActors
	);

	for (AActor* Actor : FoundActors)
	{
		if (ARoomSignActor* Sign = Cast<ARoomSignActor>(Actor))
		{
			RoomSigns.Add(Sign);
		}
	}
}
#pragma endregion

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
        TargetActor->SetActorRelativeLocation(FVector(0.f, 0.f, 10.f));
    }
}

void AAnomaly_Object_SignDrop::ExecuteSignDrop()
{
    if (RoomSigns.Num() == 0) return;

    int32 RandomIndex = FMath::RandRange(0, RoomSigns.Num() - 1);
    ARoomSignActor* TargetSign = RoomSigns[RandomIndex];

    if (!TargetSign) return;

    OriginalTransform = TargetSign->GetActorTransform();

    TargetSign->DropSign();

    FTimerHandle AttachTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(
        AttachTimerHandle,
        FTimerDelegate::CreateWeakLambda(this, [this, TargetSign]()
            {
                if (!IsValid(this) || !IsValid(TargetSign)) return;

                SetActorLocationAndRotation(TargetSign->GetActorLocation(), TargetSign->GetActorRotation());
                AttachSignToMe(TargetSign);
            }),
        1.0f,
        false
    );

    RoomSigns.RemoveAt(RandomIndex);
}

#pragma endregion

#pragma region Interact

void AAnomaly_Object_SignDrop::SetInteraction()
{
    Component_Interact->AdditionalAction = [this]()
        {
            if (bSolved) return;
            bSolved = true;

            TArray<AActor*> AttachedActors;
            GetAttachedActors(AttachedActors);
            for (AActor* Attached : AttachedActors)
            {
                if (UPrimitiveComponent* RootPrim = Cast<UPrimitiveComponent>(Attached->GetRootComponent()))
                {
                    RootPrim->SetSimulatePhysics(false);
                }
            }

            RestoreObjectTransform();
        };
}

#pragma endregion