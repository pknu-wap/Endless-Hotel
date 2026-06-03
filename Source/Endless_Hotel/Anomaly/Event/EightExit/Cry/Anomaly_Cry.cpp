// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/Cry/Anomaly_Cry.h"
#include <Components/AudioComponent.h>

#pragma region Base

AAnomaly_Cry::AAnomaly_Cry(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AC->OnAudioFinished.AddUniqueDynamic(this, &ThisClass::PlayCrySound);
}

void AAnomaly_Cry::BeginPlay()
{
	Super::BeginPlay();

	AC->SetWorldLocation(CryLocation);
}

#pragma endregion

#pragma region Activity

void AAnomaly_Cry::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyID::Cry:
		ActiveTrigger();
		break;
	}
}

void AAnomaly_Cry::DisableAnomaly()
{
	Super::DisableAnomaly();

	AC->Stop();
}

void AAnomaly_Cry::StartAnomalyAction()
{
	PlayCrySound();
}

#pragma endregion

#pragma region Cry

void AAnomaly_Cry::PlayCrySound()
{
	AC->Sound = Sound_Cry;
	AC->Play();
}

#pragma endregion