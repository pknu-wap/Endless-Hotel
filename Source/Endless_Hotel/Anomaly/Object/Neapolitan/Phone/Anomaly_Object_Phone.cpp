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

	Timeline_Ringing = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_Ringing"));
}

void AAnomaly_Object_Phone::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = SM_Receiver->GetRelativeLocation();
	UpLocation = OriginalLocation;
	UpLocation.Z += MoveValue;

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
	AC->Stop();

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

	switch (Component_Interact->GetSelectedInteraction().InteractType)
	{
	case EInteractType::TurnOff:
		Component_Interact->AdditionalAction = ([this]()
			{
				// 예시로 남겨둠
			});
		break;

	case EInteractType::Call:
		Component_Interact->AdditionalAction = ([this]()
			{
				AC->SetSound(SW_Voice);
				AC->Play();
			});
		break;
	}
}

#pragma endregion

#pragma region Ringing

void AAnomaly_Object_Phone::RingingPhone()
{	
	GetWorld()->GetTimerManager().SetTimer(UpHandle, this, &ThisClass::MovePhone, 1, false);
	GetWorld()->GetTimerManager().SetTimer(ShakeHandle, this, &ThisClass::ShakePhone, 2, false);
	GetWorld()->GetTimerManager().SetTimer(DownHandle, this, &ThisClass::MovePhone, 9, false);
}

void AAnomaly_Object_Phone::MovePhone()
{
	FVector Target = bUp ? UpLocation : OriginalLocation;

	FVector Current = FMath::VInterpTo(SM_Receiver->GetRelativeLocation(), Target, GetWorld()->GetDeltaSeconds(), 1);
	SM_Receiver->SetRelativeLocation(Current);

	if (FMath::IsNearlyEqual(Current.Z, Target.Z))
	{
		bUp = !bUp;

		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

		return;
	}

	if (!bUp)
	{
		RingingPhone();
	}
}

void AAnomaly_Object_Phone::ShakePhone()
{
	AC->Play();

	Timeline_Ringing->PlayFromStart();
}

void AAnomaly_Object_Phone::UpdateShake(float Value)
{
	FRotator Target = SM_Receiver->GetRelativeRotation();
	Target.Roll = Value;
	SM_Receiver->SetRelativeRotation(Target);
}

#pragma endregion