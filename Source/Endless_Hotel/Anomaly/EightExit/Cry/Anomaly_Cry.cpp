// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Cry/Anomaly_Cry.h"
#include "Components/AudioComponent.h"

#pragma region Base

AAnomaly_Cry::AAnomaly_Cry(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AC->OnAudioFinished.AddDynamic(this, &ThisClass::PlayCrySound);
}

#pragma endregion

#pragma region Activity

void AAnomaly_Cry::ActivateAnomaly(uint8 Anomaly_ID)
{
	Super::ActivateAnomaly(Anomaly_ID);

	FTimerHandle SoundHandle;
	GetWorld()->GetTimerManager().SetTimer(SoundHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			PlayCrySound();
		}), 20, false);
}

#pragma endregion

#pragma region Cry

void AAnomaly_Cry::PlayCrySound()
{
	AC->Sound = Sound_Cry;
	AC->Play();
}

#pragma endregion