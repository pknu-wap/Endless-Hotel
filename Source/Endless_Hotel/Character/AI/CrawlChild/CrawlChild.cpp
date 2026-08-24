// Copyright by 2026-1 WAP Game 2 team

#include "Character/AI/CrawlChild/CrawlChild.h"
#include "CrawlChildAnimInstance.h"
#include "Anomaly/Event/EightExit/CrawlChild/Anomaly_CrawlChild.h"
#include "Anomaly/Object/EightExit/CrawlChild/Anomaly_Object_CrawlChild.h"
#include "Anomaly/Object/EightExit/CrawlChild/AAnomaly_Object_WChair.h"
#include "Player/Character/EHPlayer.h"
#include "Player/Controller/EHPlayerController.h"
#include <Components/BoxComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

#pragma region Base

ACrawlChild::ACrawlChild(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACrawlChild::BeginPlay()
{
	Super::BeginPlay();
	TriggerBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnTriggerBox);
	this->SetActorEnableCollision(true);
}

#pragma endregion

#pragma region Setting

void ACrawlChild::SetOwnerAnomalyEvent(AAnomaly_CrawlChild* NewEvent)
{
	OwnerAnomalyEvent = NewEvent;
}

#pragma endregion

#pragma region CatchPlayer

void ACrawlChild::DetachFromPlayer()
{
	const FDetachmentTransformRules DetachRules(EDetachmentRule::KeepWorld, true);
	this->DetachFromActor(DetachRules);
}

#pragma endregion

#pragma region Trigger

void ACrawlChild::OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto* Player = Cast<AEHPlayer>(OtherActor);
	if (!Player)
	{
		return;
	}
	auto* PC = Cast<AEHPlayerController>(Player->GetController());
	auto* PlayerMesh = Player->GetMesh();
	UCharacterMovementComponent* Move = Player->GetCharacterMovement();
	const FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);
	this->AttachToComponent(PlayerMesh, AttachRules, SocketName);
	SetActorRelativeTransform(SocketSetting);

	this->SetActorEnableCollision(false);
	PC->bCanRun = false;
	PC->bIsRunning = false;
	PC->bCanCrouch = false;
	Move->MaxWalkSpeed = LockSpeed;
	if (OwnerAnomalyEvent.IsValid())
	{
		OwnerAnomalyEvent->DispatchToObject<AAnomaly_Object_CrawlChild>(&AAnomaly_Object_CrawlChild::ActiveTriggerBox);
	}
	if (UCrawlChildAnimInstance* AnimInstance = Cast<UCrawlChildAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		AnimInstance->bIsCrawling = false;
		AnimInstance->bIsFalling = false;
	}
}

#pragma endregion