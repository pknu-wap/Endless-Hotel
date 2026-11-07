// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/Clock/Anomaly_Object_Clock.h"
#include <Components/TimelineComponent.h>
#include <Components/AudioComponent.h>

#pragma region Base

AAnomaly_Object_Clock::AAnomaly_Object_Clock(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	SM_Bar = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Bar"));
	SM_Bar->SetupAttachment(Object);

	SM_HourHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_HourHand"));
	SM_HourHand->SetupAttachment(Object);

	SM_MinuteHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_MinuteHand"));
	SM_MinuteHand->SetupAttachment(Object);

	Timeline_TikTok = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_TikTok"));

	AC_TikTok = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_TikTok"));
	AC_TikTok->SetupAttachment(Object);
	AC_TikTok->SetAutoActivate(false);

	AC_Ringing = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_Ringing"));
	AC_Ringing->SetupAttachment(Object);
	AC_Ringing->OnAudioFinished.AddUniqueDynamic(this, &ThisClass::RingingClock);
}

void AAnomaly_Object_Clock::BeginPlay()
{
	Super::BeginPlay();

	OriginalRotation = SM_Bar->GetRelativeRotation();

	OriginalHourHandRotation = SM_HourHand->GetRelativeRotation();
	OriginalMinuteHandRotation = SM_MinuteHand->GetRelativeRotation();

	AC_TikTok->SetAutoActivate(false);
	AC_TikTok->Stop();

	FOnTimelineFloat Update_TikTok;
	Update_TikTok.BindUFunction(this, "UpdateTikTok");
	Timeline_TikTok->AddInterpFloat(CV_TikTok, Update_TikTok);

	FOnTimelineEvent Finish_TikTok;
	Finish_TikTok.BindUFunction(this, "StartTikTok");
	Timeline_TikTok->SetTimelineFinishedFunc(Finish_TikTok);

	Timeline_TikTok->PlayFromStart();
}

void AAnomaly_Object_Clock::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ClockElapsed += static_cast<double>(DeltaSeconds) * ClockSpeed;

	if (ClockElapsed < 1.0)
	{
		return;
	}

	const double PassedSteps = FMath::FloorToDouble(ClockElapsed);
	ClockElapsed -= PassedSteps;

	constexpr double ClockSecondsPerStep = 60.0;
	constexpr int32 SecondsPerCycle = 12 * 60 * 60;

	const int32 PassedSecondsInCycle = static_cast<int32>(FMath::Fmod(PassedSteps * ClockSecondsPerStep, static_cast<double>(SecondsPerCycle)));

	ClockSeconds = (ClockSeconds + PassedSecondsInCycle) % SecondsPerCycle;

	MoveClockHands();
}

#pragma endregion

#pragma region Clock

void AAnomaly_Object_Clock::SetClockSpeed(float Value)
{
	ClockSpeed = FMath::Max(Value, 0.01f);
	Timeline_TikTok->SetPlayRate(ClockSpeed);
}

void AAnomaly_Object_Clock::MoveClockHands()
{
	constexpr double MinuteAnglePerSecond = 360.0 / 3600.0;

	const double MinuteAngle = FMath::Fmod(ClockSeconds * MinuteAnglePerSecond, 360.0);

	const int32 PassedHours = ClockSeconds / 3600;
	const double HourAngle = PassedHours * 30.0;

	FRotator MinuteTarget = OriginalMinuteHandRotation;
	MinuteTarget.Pitch -= MinuteAngle;
	SM_MinuteHand->SetRelativeRotation(MinuteTarget);

	FRotator HourTarget = OriginalHourHandRotation;
	HourTarget.Pitch -= HourAngle;
	SM_HourHand->SetRelativeRotation(HourTarget);

	PlayTikTokSound();
}

#pragma endregion

#pragma region Interact

void AAnomaly_Object_Clock::Interact(AEHCharacter* Interacter)
{
	Super::Interact(Interacter);

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
	USoundBase* Sound = bPlayTick ? Sound_Tick.Get() : Sound_Tock.Get();
	bPlayTick = !bPlayTick;
	AC_TikTok->SetSound(Sound);
	AC_TikTok->Play();
}

#pragma endregion

#pragma region Ringing

void AAnomaly_Object_Clock::RingingClock()
{
	Component_Interact->ActiveInteract(true);

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