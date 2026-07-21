// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/CrawlChild/Anomaly_Object_CrawlChild.h"
#include "Player/Controller/EHPlayerController.h"
#include "Player/Character/EHPlayer.h"
#include "UI/Controller/UI_Controller.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/BoxComponent.h>

#pragma region Base

AAnomaly_Object_CrawlChild::AAnomaly_Object_CrawlChild(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAnomaly_Object_CrawlChild::BeginPlay()
{
	Super::BeginPlay();
	TriggerBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnTriggerBox);
}

#pragma endregion

#pragma region Trigger

void AAnomaly_Object_CrawlChild::OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto* Player = Cast<AEHPlayer>(OtherActor);
	if (!Player)
	{
		return;
	}
	this->SetActorTransform(StartTransform);
	Object->SetSimulatePhysics(true);
	Object->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Object->WakeAllRigidBodies();
}

#pragma endregion