// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/Twin/Anomaly_Object_Twin.h"
#include "Player/Character/EHPlayer.h"
#include <Components/BoxComponent.h>

#pragma region Base

AAnomaly_Object_Twin::AAnomaly_Object_Twin(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAnomaly_Object_Twin::BeginPlay()
{
	Super::BeginPlay();
	TriggerBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnTriggerBox);
}

#pragma endregion

#pragma region Twin

void AAnomaly_Object_Twin::StartTwin()
{
	SetActorTransform(TwinTransform);
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AAnomaly_Object_Twin::OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEHPlayer* Player = Cast<AEHPlayer>(OtherActor);
	if (!Player)
	{
		return;
	}
	Player->DieDelegate.Broadcast(EDeathReason::Burn);
}

#pragma endregion