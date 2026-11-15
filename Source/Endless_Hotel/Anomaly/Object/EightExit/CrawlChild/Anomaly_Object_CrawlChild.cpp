// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Object/EightExit/CrawlChild/Anomaly_Object_CrawlChild.h"
#include "Anomaly/Object/EightExit/Ceiling/Anomaly_Object_Ceiling.h"
#include "Anomaly/Event/EightExit/CrawlChild/Anomaly_CrawlChild.h"
#include "Character/AI/CrawlChild/CrawlChild.h"
#include "Player/Character/EHPlayer.h"
#include "Player/Controller/EHPlayerController.h"
#include <Components/AudioComponent.h>
#include <Components/BoxComponent.h>
#include <NiagaraComponent.h>

#pragma region Base

AAnomaly_Object_CrawlChild::AAnomaly_Object_CrawlChild(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);
    TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    TriggerBox->SetGenerateOverlapEvents(true);

    ObjectAC = CreateDefaultSubobject<UAudioComponent>(TEXT("ObjectAC"));
    ObjectAC->SetupAttachment(RootComponent);
    ObjectAC->SetAutoActivate(false);

    ChildAC = CreateDefaultSubobject<UAudioComponent>(TEXT("ChildAC"));
    ChildAC->SetupAttachment(RootComponent);
    ChildAC->SetAutoActivate(false);

    PillNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PillNiagara"));
    PillNiagara->SetupAttachment(RootComponent);
    PillNiagara->SetAutoActivate(false);
}

void AAnomaly_Object_CrawlChild::BeginPlay()
{
    Super::BeginPlay();

    TriggerBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnTriggerBox);

    Object->SetVisibility(false, false);
    Object->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    PillNiagara->SetVisibility(false);
}

#pragma endregion

#pragma region ReadyAnomaly

void AAnomaly_Object_CrawlChild::SetupCrawlChildObject()
{
    GetWorldTimerManager().ClearTimer(PillSpawnTimer);
    GetWorldTimerManager().ClearTimer(ChildReleaseTimer);

    PillNiagara->DeactivateImmediate();
    PillNiagara->SetVisibility(false);

    Object->SetWorldTransform(StartTransform);
    Object->SetVisibility(false, false);
    Object->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    ObjectAC->Stop();
    ChildAC->Stop();
}

void AAnomaly_Object_CrawlChild::OnCrawlChildSpawnedHandler(ACrawlChild* SpawnedCrawlChild)
{
    CrawlChild = SpawnedCrawlChild;
}

#pragma endregion

#pragma region Trigger

void AAnomaly_Object_CrawlChild::ActiveTriggerBox()
{
    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AAnomaly_Object_CrawlChild::OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AEHPlayer* Player = Cast<AEHPlayer>(OtherActor);
    if (!Player)
    {
        return;
    }

    TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    StartPillCollapse();

    AEHPlayerController* PC = Cast<AEHPlayerController>(Player->GetController());
    PC->bCanRun = true;
    PC->bIsRunning = true;
    PC->bCanCrouch = true;

    Player->SetWalkSpeed(WALK_SPEED);
}

#pragma endregion

#pragma region Collapse

void AAnomaly_Object_CrawlChild::StartPillCollapse()
{
    if (PillNiagara->GetAsset())
    {
        const FTransform ActorTransform = GetActorTransform();
        const FVector Duration = FVector::ZeroVector;
        PillNiagara->SetWorldLocation(AIEndTransform.GetLocation() + SpawnCenter);

        PillNiagara->SetVariableInt(TEXT("User.PillCount"), PillCount);
        PillNiagara->SetVariableFloat(TEXT("User.SpawnRate"), PillCount / FMath::Max(PillSpawnDuration, 0.1f));
        PillNiagara->SetVariablePosition(TEXT("User.WallPoint"), ActorTransform.TransformPosition(WallPoint));
        PillNiagara->SetVariablePosition(TEXT("User.CornerPoint"), ActorTransform.TransformPosition(CornerPoint));
        PillNiagara->SetVariablePosition(TEXT("User.HallEndPoint"), ActorTransform.TransformPosition(HallEndPoint));

        PillNiagara->SetVisibility(true);
        PillNiagara->Activate(true);

        GetWorldTimerManager().SetTimer(PillSpawnTimer, this, &ThisClass::StopPillSpawn, FMath::Max(PillSpawnDuration, 0.1f), false);
    }

    GetWorldTimerManager().SetTimer(ChildReleaseTimer, this, &ThisClass::ReleaseChild, FMath::Max(ChildReleaseDelay, 0.01f), false);
}

void AAnomaly_Object_CrawlChild::StopPillSpawn()
{
    PillNiagara->Deactivate();
}

void AAnomaly_Object_CrawlChild::ReleaseChild()
{
    if (ACrawlChild* Child = CrawlChild.Get())
    {
        Child->DetachFromPlayer();
        Child->SetActorTransform(AIEndTransform);
    }

    ObjectAC->Play();
    ChildAC->Play();
}

#pragma endregion