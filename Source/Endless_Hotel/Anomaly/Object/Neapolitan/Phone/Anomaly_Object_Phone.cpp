// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/Phone/Anomaly_Object_Phone.h"
#include <Components/AudioComponent.h>
#include <Components/TimelineComponent.h>

#pragma region Base

AAnomaly_Object_Phone::AAnomaly_Object_Phone(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AC"));
	AC->SetupAttachment(Object);
	AC->SetAutoActivate(false);

	Timeline_Ringing = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_Ringing"));
}

void AAnomaly_Object_Phone::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetActorLocation();
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

	GetWorld()->GetTimerManager().ClearTimer(MoveHandle);
	GetWorld()->GetTimerManager().ClearTimer(ShakeHandle);

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
	GetWorld()->GetTimerManager().SetTimer(MoveHandle, this, &ThisClass::MovePhone, 1, true);
	GetWorld()->GetTimerManager().SetTimer(ShakeHandle, this, &ThisClass::ShakePhone, 2, false);
	GetWorld()->GetTimerManager().SetTimer(MoveHandle, this, &ThisClass::MovePhone, 9, true);
}

void AAnomaly_Object_Phone::MovePhone()
{
	FVector Target = bUp ? UpLocation : OriginalLocation;

	FVector Current = FMath::VInterpTo(GetActorLocation(), Target, GetWorld()->GetDeltaSeconds(), 5);
	SetActorLocation(Current);

	if (FMath::IsNearlyEqual(Current.Z, Target.Z))
	{
		bUp = !bUp;
		GetWorld()->GetTimerManager().ClearTimer(MoveHandle);
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
	FRotator Target = GetActorRotation();
	Target.Pitch = Value;
	SetActorRotation(Target);
}

#pragma endregion