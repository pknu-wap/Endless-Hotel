// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Clock/Anomaly_Object_Clock.h"
#include <Components/TimelineComponent.h>
#include <Components/AudioComponent.h>

#pragma region Base

#define LOCTEXT_NAMESPACE "Clock"

AAnomaly_Object_Clock::AAnomaly_Object_Clock(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SM_Bar = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Bar"));
	SM_Bar->SetupAttachment(Object);

	Timeline_TikTok = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_TikTok"));

	DescriptionText = LOCTEXT("Key1", "알람 끄기");

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

#undef LOCTEXT_NAMESPACE

#pragma endregion

#pragma region Interact

void AAnomaly_Object_Clock::Interacted_Implementation()
{
	if (bInTime)
	{
		bSolved = true;
		AC_Ringing->OnAudioFinished.Clear();
		GetWorld()->GetTimerManager().ClearTimer(TurnOffHandle);
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
	AC_Ringing->Play();
	bInTime = true;

	GetWorld()->GetTimerManager().SetTimer(TurnOffHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			bInTime = false;
			AC_Ringing->OnAudioFinished.Clear();
		}), 30, false);
}

#pragma endregion