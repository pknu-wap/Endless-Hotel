// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Object/EightExit/CrawlChild/Anomaly_Object_CrawlChild.h"
#include "Anomaly/Object/EightExit/Ceiling/Anomaly_Object_Ceiling.h"
#include "Anomaly/Event/EightExit/CrawlChild/Anomaly_CrawlChild.h"
#include "Character/AI/CrawlChild/CrawlChild.h"
#include "Player/Character/EHPlayer.h"
#include "Player/Controller/EHPlayerController.h"
#include <Components/AudioComponent.h>
#include <Components/BoxComponent.h>
#include <Components/InstancedStaticMeshComponent.h>
#include <Components/StaticMeshComponent.h>
#include <TimerManager.h>

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

    PillISM = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("PillISM"));
    PillISM->SetupAttachment(RootComponent);
    PillISM->SetMobility(EComponentMobility::Movable);
    PillISM->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    PillISM->SetGenerateOverlapEvents(false);
    PillISM->SetCanEverAffectNavigation(false);
}

void AAnomaly_Object_CrawlChild::BeginPlay()
{
    Super::BeginPlay();

    TriggerBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnTriggerBox);

    const int32 Count = PillISM->GetInstanceCount();
    PillScales.SetNum(Count);

    for (int32 Index = 0; Index < Count; ++Index)
    {
        FTransform InstanceTransform;
        PillISM->GetInstanceTransform(Index, InstanceTransform, false);
        PillScales[Index] = InstanceTransform.GetScale3D();
    }

    Object->SetVisibility(false, false);
    Object->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    PillISM->SetVisibility(false);
}

#pragma endregion

#pragma region ReadyAnomaly

void AAnomaly_Object_CrawlChild::SetupCrawlChildObject()
{
    GetWorldTimerManager().ClearTimer(PillSpawnTimer);
    GetWorldTimerManager().ClearTimer(ChildReleaseTimer);

    ClearPhysicsPills();

    Object->SetWorldTransform(StartTransform);
    Object->SetVisibility(false, false);
    Object->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    PillISM->SetVisibility(false);

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

    OwnerAnomalyEvent->DispatchToObject<AAnomaly_Object_Ceiling>(&AAnomaly_Object_Ceiling::TriggerCeilingCollapse);

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
    if (!PillISM->GetStaticMesh() || PillScales.IsEmpty())
    {
        return;
    }

    SpawnPillBatch();

    if (PhysicsPills.Num() < PillScales.Num())
    {
        GetWorldTimerManager().SetTimer(PillSpawnTimer, this, &ThisClass::SpawnPillBatch, FMath::Max(BatchInterval, 0.01f), true);
    }

    GetWorldTimerManager().SetTimer(ChildReleaseTimer, this, &ThisClass::ReleaseChild, FMath::Max(ChildReleaseDelay, 0.01f), false);
}

void AAnomaly_Object_CrawlChild::SpawnPillBatch()
{
    const int32 Count = PillScales.Num();
    const int32 BatchSize = FMath::Max(PillsPerBatch, 1);
    const int32 Columns = FMath::CeilToInt(FMath::Sqrt(static_cast<float>(BatchSize)));
    const int32 Rows = FMath::DivideAndRoundUp(BatchSize, Columns);
    const FVector BaseLocation = AIEndTransform.GetLocation() + SpawnCenter;
    const FVector ISMWorldScale = PillISM->GetComponentScale();

    for (int32 Slot = 0; Slot < BatchSize && PhysicsPills.Num() < Count; ++Slot)
    {
        const int32 Index = PhysicsPills.Num();
        const int32 Column = Slot % Columns;
        const int32 Row = Slot / Columns;

        const FVector SpawnOffset((Column - (Columns - 1) * 0.5f) * SpawnSpacing, (Row - (Rows - 1) * 0.5f) * SpawnSpacing, 0.f);
        const FVector WorldLocation = BaseLocation + SpawnOffset;
        const FQuat WorldRotation = FRotator(0.f, FMath::FRandRange(-180.f, 180.f), 0.f).Quaternion();
        const FVector WorldScale = ISMWorldScale * PillScales[Index];

        UStaticMeshComponent* Pill = NewObject<UStaticMeshComponent>(this);
        Pill->SetMobility(EComponentMobility::Movable);
        Pill->SetStaticMesh(PillISM->GetStaticMesh());

        for (int32 MaterialIndex = 0; MaterialIndex < PillISM->GetNumMaterials(); ++MaterialIndex)
        {
            Pill->SetMaterial(MaterialIndex, PillISM->GetMaterial(MaterialIndex));
        }

        Pill->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        Pill->SetCollisionObjectType(ECC_PhysicsBody);
        Pill->SetCollisionResponseToAllChannels(ECR_Block);
        Pill->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
        Pill->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
        Pill->SetGenerateOverlapEvents(false);
        Pill->SetCanEverAffectNavigation(false);

        Pill->SetWorldTransform(FTransform(WorldRotation, WorldLocation, WorldScale));
        Pill->RegisterComponent();

        Pill->SetMassOverrideInKg(NAME_None, PillMassKg, true);
        Pill->SetLinearDamping(PillLinearDamping);
        Pill->SetAngularDamping(PillAngularDamping);
        Pill->SetUseCCD(true);
        Pill->SetEnableGravity(true);
        Pill->SetSimulatePhysics(true);

        PhysicsPills.Add(Pill);
    }

    if (PhysicsPills.Num() >= Count)
    {
        GetWorldTimerManager().ClearTimer(PillSpawnTimer);
    }
}

void AAnomaly_Object_CrawlChild::ClearPhysicsPills()
{
    for (UStaticMeshComponent* Pill : PhysicsPills)
    {
        Pill->DestroyComponent();
    }

    PhysicsPills.Reset();
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