// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/Twin/Anomaly_Object_Twin.h"
#include "Player/Character/EHPlayer.h"
#include "Player/Controller/EHPlayerController.h"
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>

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
	FreezeWhenObserved();
}

#pragma endregion

#pragma region Move

void AAnomaly_Object_Twin::FreezeWhenObserved()
{
	GetWorld()->GetTimerManager().SetTimer(TwinTimerHandle,
		FTimerDelegate::CreateWeakLambda(this, [this]()
			{
				AEHPlayer* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
				if (!Player)
				{
					return;
				}

				AEHPlayerController* PC = Cast<AEHPlayerController>(Player->Controller);
				if (!PC)
				{
					return;
				}

				bool bObserved = PC->IsLookingAtActor(this, DetectDistance);
				UpdateTwinState(bObserved);
				if (CurrentState == ETwinState::Moving)
				{
					MoveTowardPlayer();
				}
			}), 0.1f, true);
}

void AAnomaly_Object_Twin::UpdateTwinState(bool bObserved)
{
	ETwinState NewState = bObserved ? ETwinState::Frozen : ETwinState::Moving;

	if (CurrentState == NewState)
	{
		return;
	}

	CurrentState = NewState;

	if (CurrentState == ETwinState::Frozen)
	{
		TriggerBox->SetBoxExtent(MinTriggerSize);
	}
	else
	{
		TriggerBox->SetBoxExtent(KillTriggerSize);
	}
}

void AAnomaly_Object_Twin::MoveTowardPlayer()
{
	AEHPlayer* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Player)
	{
		return;
	}

	FVector Direction = (Player->GetActorLocation() - GetActorLocation());
	Direction.Z = 0;
	Direction = Direction.GetSafeNormal();
	SetActorLocation(GetActorLocation() + Direction * MoveSpeed * 0.1f, false, nullptr, ETeleportType::TeleportPhysics);
}

#pragma endregion

#pragma region Trigger

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