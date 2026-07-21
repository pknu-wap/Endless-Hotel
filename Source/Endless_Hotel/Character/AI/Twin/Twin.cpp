// Copyright by 2026-1 WAP Game 2 team

#include "Character/AI/Twin/Twin.h"
#include "Player/Character/EHPlayer.h"
#include <Components/BoxComponent.h>

ATwin::ATwin(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);
    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ATwin::BeginPlay()
{
    Super::BeginPlay();
    if (TriggerBox)
    {
        TriggerBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnTriggerBox);
    }
    CustomTimeDilation = 0.0f;
}

void ATwin::SetTwinState(ETwinState NewState)
{
    if (CurrentState == NewState)
    {
        return;
    }
	CurrentState = NewState;
	CustomTimeDilation = CurrentState == ETwinState::Frozen ? 0.0f : 1.0f;
}

void ATwin::OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AEHPlayer* Player = Cast<AEHPlayer>(OtherActor);
    if (!Player)
    {
        return;
    }
    Player->DieDelegate.Broadcast(EDeathReason::Burn);
}