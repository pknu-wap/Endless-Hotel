// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Object/EightExit/CrawlChild/Anomaly_Object_CrawlChild.h"
#include "Anomaly/Event/EightExit/CrawlChild/Anomaly_CrawlChild.h"
#include "Character/AI/CrawlChild/CrawlChild.h"
#include "Character/AI/CrawlChild/CrawlChildController.h"
#include "Player/Character/EHPlayer.h"
#include "Player/Controller/EHPlayerController.h"
#include "UI/Controller/UI_Controller.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/BoxComponent.h>
#include <Components/TimelineComponent.h>
#include <Components/AudioComponent.h>

#pragma region Base

AAnomaly_Object_CrawlChild::AAnomaly_Object_CrawlChild(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ObjectAC = CreateDefaultSubobject<UAudioComponent>(TEXT("ObjectAC"));
	ObjectAC->SetupAttachment(RootComponent);

	ChildAC = CreateDefaultSubobject<UAudioComponent>(TEXT("ChildAC"));
	ChildAC->SetupAttachment(RootComponent);

	FallTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("FallTimeline"));
}

void AAnomaly_Object_CrawlChild::BeginPlay()
{
	Super::BeginPlay();
	TriggerBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnTriggerBox);
	FOnTimelineFloat UpdateFunc;
	FOnTimelineEvent FinishedFunc;

	UpdateFunc.BindUFunction(this, FName("OnFallTimelineUpdate"));
	FallTimeline->AddInterpFloat(FallCurve, UpdateFunc);
	FinishedFunc.BindUFunction(this, FName("OnFallTimelineFinished"));
	FallTimeline->SetTimelineFinishedFunc(FinishedFunc);
}

#pragma endregion

#pragma region ReadyAnomaly

void AAnomaly_Object_CrawlChild::SetupCrawlChildObject()
{
	auto* VerdictSub = GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();
	AAnomaly_CrawlChild* OwnerEvent = Cast<AAnomaly_CrawlChild>(VerdictSub->CurrentAnomaly);
	OwnerEvent->OnCrawlChildSpawned.AddUniqueDynamic(this, &ThisClass::OnCrawlChildSpawnedHandler);
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TriggerBox->SetWorldTransform(TriggerBox_Transform);
	Object->SetWorldTransform(StartTransform);
	Object->SetVisibility(false);
	Object->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

#pragma endregion

#pragma region Trigger

void AAnomaly_Object_CrawlChild::ActiveTriggerBox()
{
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AAnomaly_Object_CrawlChild::OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto* Player = Cast<AEHPlayer>(OtherActor);
	if (!Player)
	{
		return;
	}
	Object->SetVisibility(true);
	FallTimeline->PlayFromStart();
	auto* PC = Cast<AEHPlayerController>(Player->GetController());
	UCharacterMovementComponent* Move = Player->GetCharacterMovement();
	PC->bCanRun = true;
	PC->bIsRunning = true;
	PC->bCanCrouch = true;
	Move->MaxWalkSpeed = PC->WalkSpeed;
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

#pragma endregion

#pragma region Collapse

void AAnomaly_Object_CrawlChild::OnFallTimelineUpdate(float Alpha)
{
	SetActorLocation(FMath::Lerp(StartTransform.GetLocation(), EndTransform.GetLocation(), Alpha));
}

void AAnomaly_Object_CrawlChild::OnFallTimelineFinished()
{
	SetActorTransform(EndTransform);
	CrawlChild->DetachFromPlayer();
	CrawlChild->SetActorTransform(AIEndTransform);
	Object->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ObjectAC->Play();
	ChildAC->Play();
}

#pragma endregion

#pragma region AI

void AAnomaly_Object_CrawlChild::OnCrawlChildSpawnedHandler(ACrawlChild* SpawnedCrawlChild)
{
	this->CrawlChild = SpawnedCrawlChild;
	SpawnedCrawlChild->AnomalyObjectRef = this;
}

#pragma endregion