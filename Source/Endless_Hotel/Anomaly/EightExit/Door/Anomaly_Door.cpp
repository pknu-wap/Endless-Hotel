// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Door/Anomaly_Door.h"
#include "Anomaly/Object/Door/Anomaly_Object_Door.h"
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>

#pragma region Base

AAnomaly_Door::AAnomaly_Door(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	TriggerBox_Open = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox_Open"));
	TriggerBox_Open->SetupAttachment(RootComponent);
	TriggerBox_Close->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	TriggerBox_Close = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox_Close"));
	TriggerBox_Close->SetupAttachment(RootComponent);
	TriggerBox_Close->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

#pragma endregion

#pragma region Activity

void AAnomaly_Door::SetAnomalyActivate()
{
	Super::SetAnomalyActivate();

	switch (AnomalyName)
	{
	case EAnomalyName::Door_Shake:
		AnomalyAction = ([this](AAnomaly_Object_Base* AnomalyObject)
			{
				Cast<AAnomaly_Object_Door>(AnomalyObject)->DoorShaking();
			});
		ActiveTrigger();
		break;

	case EAnomalyName::Door_Close:
		SetupDoorTrigger();
		ActiveTrigger();
		break;
	}
}

#pragma endregion

#pragma region Trigger

void AAnomaly_Door::SetupDoorTrigger()
{
	TriggerTargetDoor = nullptr;

	for (AActor* Found : LinkedObjects)
	{
		AAnomaly_Object_Door* Door = Cast<AAnomaly_Object_Door>(Found);
		if (Door->DoorIndex == 8)
		{
			TriggerTargetDoor = Door;
			break;
		}
	}
	TriggerBox_Open->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox_Open->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	TriggerBox_Close->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TriggerBox_Close->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	TriggerBox_Open->OnComponentBeginOverlap.AddDynamic(this, &AAnomaly_Door::OnTriggerBox_OpenBeginOverlap);
	TriggerBox_Close->OnComponentBeginOverlap.AddDynamic(this, &AAnomaly_Door::OnTriggerBox_CloseBeginOverlap);
}

void AAnomaly_Door::OnTriggerBox_OpenBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OverlappedComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TriggerTargetDoor->OpenDoor();

	TriggerBox_Open->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TriggerBox_Close->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AAnomaly_Door::OnTriggerBox_CloseBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OverlappedComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TriggerTargetDoor->CloseDoor();

	TriggerBox_Close->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TriggerBox_Open->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
#pragma endregion