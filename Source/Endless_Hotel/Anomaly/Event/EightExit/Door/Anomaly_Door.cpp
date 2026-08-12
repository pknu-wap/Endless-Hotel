// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/Door/Anomaly_Door.h"
#include "Anomaly/Object/EightExit/Door/Anomaly_Object_Door.h"
#include "Player/Character/EHPlayer.h"
#include <TimerManager.h>
#include <Components/BoxComponent.h>

#pragma region Base

AAnomaly_Door::AAnomaly_Door(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

#pragma endregion

#pragma region Activity

void AAnomaly_Door::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyID)
	{
	case EAnomalyID::Door_Shake:
		SetupAnomalyAction<AAnomaly_Object_Door>(&AAnomaly_Object_Door::StartShaking);
		ActiveTrigger();`
		break;

	//case EAnomalyID::Door_Close:
	//	CurrentDoorState = EDoorSequenceState::OpenDoor;
	//	TriggerBox->SetWorldTransform(OpenDoorTriggerTrans);
	//	ActiveTrigger();
	//	break;
	}
}

#pragma endregion

//#pragma region Trigger
//
//void AAnomaly_Door::OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	AEHPlayer* Player = Cast<AEHPlayer>(OtherActor);
//	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//	AdvanceDoorState();
//}
//
//#pragma endregion

//#pragma region DoorSequence
//
//void AAnomaly_Door::AdvanceDoorState()
//{
//	AAnomaly_Object_Door* Door = nullptr;
//
//	for (const auto& Target : TargetAnomalyObjects)
//	{
//		Door = Cast<AAnomaly_Object_Door>(Target);
//	}
//
//	switch (CurrentDoorState)
//	{
//	case EDoorSequenceState::OpenDoor:
//	{
//		Door->OpenDoor();
//
//		TriggerBox->SetWorldTransform(OpenHandTriggerTrans);
//
//		constexpr float Delay = 0.1f;
//		FTimerHandle EnableHandle;
//
//		GetWorld()->GetTimerManager().SetTimer(EnableHandle, FTimerDelegate::CreateWeakLambda(this,[this]()
//		{
//			TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
//		}),	Delay, false);
//
//		CurrentDoorState = EDoorSequenceState::OpenHand;
//		break;
//	}
//
//	case EDoorSequenceState::OpenHand:
//	{
//		Door->PlayHandOpen();
//
//		TriggerBox->SetWorldTransform(CloseDoorTriggerTrans);
//
//		constexpr float Delay = 0.1f;
//		FTimerHandle EnableHandle;
//
//		GetWorld()->GetTimerManager().SetTimer(EnableHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
//		{
//			TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
//		}),	Delay, false);
//
//		CurrentDoorState = EDoorSequenceState::CloseHandAndDoor;
//		break;
//	}
//
//	case EDoorSequenceState::CloseHandAndDoor:
//	{
//		Door->PlayHandClose();
//		Door->CloseDoor();
//
//		CurrentDoorState = EDoorSequenceState::Finished;
//		break;
//	}
//
//	case EDoorSequenceState::Finished:
//	default:
//		break;
//	}
//}
//
//#pragma endregion