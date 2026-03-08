// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/Phone/Anomaly_Object_Phone.h"
#include <Components/AudioComponent.h>
#include <Components/TimelineComponent.h>

#pragma region Base

AAnomaly_Object_Phone::AAnomaly_Object_Phone(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SM_Receiver = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Receiver"));
	SM_Receiver->SetupAttachment(RootComponent);

	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AC"));
	AC->SetupAttachment(Object);
	AC->SetAutoActivate(false);

	Timeline_Move = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_Move"));
	Timeline_Ringing = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_Ringing"));
}

void AAnomaly_Object_Phone::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat Update_Move;
	Update_Move.BindUFunction(this, "UpdateMove");
	Timeline_Move->AddInterpFloat(CV_Move, Update_Move);

	FOnTimelineFloat Update_Ringing;
	Update_Ringing.BindUFunction(this, "UpdateShake");
	Timeline_Ringing->AddInterpFloat(CV_Ringing, Update_Ringing);
}

#pragma endregion

#pragma region Interact

void AAnomaly_Object_Phone::SetInteraction()
{
	Super::SetInteraction();

	switch (AnomalyName)
	{
	case EAnomalyName::Phone_Ringing:
		RingingInteraction();
		break;
	}
}

void AAnomaly_Object_Phone::RingingInteraction()
{
	Component_Interact->AdditionalAction = ([this]()
		{
			GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

			Timeline_Move->Stop();
			Timeline_Ringing->Stop();

			AC->Stop();

			switch (Component_Interact->GetSelectedInteraction().InteractType)
			{
			case EInteractType::TurnOff:
				break;

			case EInteractType::Call:
				AC->SetSound(SW_Voice);
				AC->Play();
				break;
			}
		});
}

#pragma endregion

#pragma region Ringing

void AAnomaly_Object_Phone::RingingPhone()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

	GetWorld()->GetTimerManager().SetTimer(MoveHandle, this, &ThisClass::MovePhone, 1, false);
	GetWorld()->GetTimerManager().SetTimer(ShakeHandle, this, &ThisClass::ShakePhone, 1.5f, false);
}

void AAnomaly_Object_Phone::MovePhone()
{
	Timeline_Move->PlayFromStart();
}

void AAnomaly_Object_Phone::ShakePhone()
{
	AC->Play();

	Timeline_Ringing->PlayFromStart();
}

void AAnomaly_Object_Phone::UpdateMove(float Value)
{
	FVector Target = SM_Receiver->GetRelativeLocation();
	Target.Z = Value;
	SM_Receiver->SetRelativeLocation(Target);
}

void AAnomaly_Object_Phone::UpdateShake(float Value)
{
	FRotator Target = SM_Receiver->GetRelativeRotation();
	Target.Roll = Value;
	SM_Receiver->SetRelativeRotation(Target);
}

#pragma endregion