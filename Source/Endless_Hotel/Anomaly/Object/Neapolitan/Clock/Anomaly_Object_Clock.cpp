// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/Clock/Anomaly_Object_Clock.h"
#include <Components/TimelineComponent.h>
#include <Components/AudioComponent.h>

#pragma region Base

AAnomaly_Object_Clock::AAnomaly_Object_Clock(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SM_Bar = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Bar"));
	SM_Bar->SetupAttachment(Object);

	Timeline_TikTok = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_TikTok"));

	AC_TikTok = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_TikTok"));
	AC_TikTok->SetupAttachment(Object);
	AC_TikTok->OnAudioFinished.AddDynamic(this, &ThisClass::PlayTikTokSound);

	AC_Ringing = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_Ringing"));
	AC_Ringing->SetupAttachment(Object);
	AC_Ringing->OnAudioFinished.AddDynamic(this, &ThisClass::RingingClock);
}

void AAnomaly_Object_Clock::BeginPlay()
{
	Super::BeginPlay();

	OriginalRotation = SM_Bar->GetRelativeRotation();

	FOnTimelineFloat Update_TikTok;
	Update_TikTok.BindUFunction(this, "UpdateTikTok");
	Timeline_TikTok->AddInterpFloat(CV_TikTok, Update_TikTok);

	FOnTimelineEvent Finish_TikTok;
	Finish_TikTok.BindUFunction(this, "StartTikTok");
	Timeline_TikTok->SetTimelineFinishedFunc(Finish_TikTok);

	Timeline_TikTok->PlayFromStart();
}

#pragma endregion

#pragma region Interact

void AAnomaly_Object_Clock::Interact_Implementation()
{
	Super::Interact_Implementation();

	FInteractInfo Info = Component_Interact->GetSelectedInteractInfo();

	switch (Info.InteractType)
	{
	case EInteractType::TurnOff:
		StopRinging();
		break;
	}
}

#pragma endregion

#pragma region TikTok

void AAnomaly_Object_Clock::StartTikTok()
{
	Timeline_TikTok->PlayFromStart();
}

void AAnomaly_Object_Clock::UpdateTikTok(float Value)
{
	FRotator Target = OriginalRotation;
	Target.Pitch = Value;
	SM_Bar->SetRelativeRotation(Target);
}

void AAnomaly_Object_Clock::PlayTikTokSound()
{
	AC_TikTok->Play();
}

#pragma endregion

#pragma region Ringing

void AAnomaly_Object_Clock::RingingClock()
{
	bSolved = false;
	AC_Ringing->Play();
	bInTime = true;

	GetWorld()->GetTimerManager().SetTimer(TurnOffHandle, this, &ThisClass::StopRinging, 30, false);
}

void AAnomaly_Object_Clock::StopRinging()
{
	if (!bInTime)
	{
		return;
	}

	AC_Ringing->OnAudioFinished.Clear();
	AC_Ringing->Stop();
	GetWorld()->GetTimerManager().ClearTimer(TurnOffHandle);
}

#pragma endregion