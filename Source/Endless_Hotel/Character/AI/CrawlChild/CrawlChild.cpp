// Copyright by 2026-1 WAP Game 2 team

#include "Character/AI/CrawlChild/CrawlChild.h"
#include "CrawlChildAnimInstance.h"
#include "Anomaly/Object/EightExit/CrawlChild/Anomaly_Object_CrawlChild.h"
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
	if (UCrawlChildAnimInstance* AnimInstance = Cast<UCrawlChildAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		AnimInstance->bIsCrawling = true;
	}
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
	SetActorRelativeLocation(SocketSetting.GetLocation());
	SetActorRelativeRotation(SocketSetting.GetRotation());
	this->SetActorEnableCollision(false);
	PC->bCanRun = false;
	PC->bIsRunning = false;
	PC->bCanCrouch = false;
	Move->MaxWalkSpeed = LockSpeed;
	AnomalyObjectRef->ActiveTriggerBox();
	if (UCrawlChildAnimInstance* AnimInstance = Cast<UCrawlChildAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		AnimInstance->bIsCrawling = false;
	}
}

#pragma endregion