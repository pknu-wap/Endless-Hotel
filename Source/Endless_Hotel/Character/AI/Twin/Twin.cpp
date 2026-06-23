// Copyright by 2026-1 WAP Game 2 team

#include "Character/AI/Twin/Twin.h"
#include "TwinAnimInstance.h"
#include "TwinController.h"
#include "Player/Character/EHPlayer.h"
#include "Player/Controller/EHPlayerController.h"
#include <Kismet/GameplayStatics.h>
#include <Components/CapsuleComponent.h>

#pragma region Base

void ATwin::BeginPlay()
{
    Super::BeginPlay();
    KillTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATwin::OnKillTriggerOverlap);
}

#pragma endregion

#pragma region Trigger

void ATwin::OnKillTriggerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AEHPlayer* Player = Cast<AEHPlayer>(OtherActor);
    if (!Player) return;

    AEHPlayerController* PC = Cast<AEHPlayerController>(Player->Controller);

    GetWorld()->GetTimerManager().ClearTimer(TwinTimerHandle);
    Player->DieDelegate.Broadcast(EDeathReason::Burn);
}

#pragma endregion

void ATwin::UpdateTwinState(bool bObserved)
{
	ETwinState NewState = bObserved ? ETwinState::Frozen : ETwinState::Moving;
	if (CurrentState == NewState)
	{
		return;
	}
	CurrentState = NewState;
    auto* AnimInstance = Cast<UTwinAnimInstance>(GetMesh()->GetAnimInstance());
    auto* TwinController = Cast<ATwinController>(GetController());

    NewState == ETwinState::Frozen ? KillTrigger->SetCapsuleRadius(MinKillDistance) : KillTrigger->SetCapsuleRadius(DefaultKillDistance);

    switch (CurrentState)
    {
    case ETwinState::Frozen:
        AnimInstance->bIsMove = false;
        TwinController->StopMovement();
        break;

    case ETwinState::Moving:
        AnimInstance->bIsMove = true;
        ACharacter* Player = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
        if (Player)
        {
            TwinController->MoveToActor(Player, MinKillDistance);
        }
        break;
    }
}

void ATwin::FreezeWhenObserved()
{
    GetWorld()->GetTimerManager().SetTimer(TwinTimerHandle,
        FTimerDelegate::CreateWeakLambda(this, [this]()
            {
                AEHPlayer* Player = Cast<AEHPlayer>(
                    UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
                if (!Player) return;

                AEHPlayerController* PC = Cast<AEHPlayerController>(Player->Controller);
                if (!PC) return;

                bool bObserved = PC->IsLookingAtActor(this, DetectDistance);
                UpdateTwinState(bObserved);
            }), 0.1f, true);
}