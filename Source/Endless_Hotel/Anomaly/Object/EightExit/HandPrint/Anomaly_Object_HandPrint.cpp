// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/EightExit/HandPrint/Anomaly_Object_HandPrint.h"
#include <Components/AudioComponent.h>
#include <Components/DecalComponent.h>

#pragma region Base

AAnomaly_Object_HandPrint::AAnomaly_Object_HandPrint(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Decal_HandPrint = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal_HandPrint"));
	SetRootComponent(Decal_HandPrint);
	Decal_HandPrint->SetVisibility(false);

	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AC->SetupAttachment(RootComponent);
	AC->SetAutoActivate(false);
}

#pragma endregion

#pragma region HandPrint

void AAnomaly_Object_HandPrint::ShowHandPrint(uint8 Index)
{
	FTimerHandle EffectHandle;
	float ShowDuration = 2.f + Index * 0.1f;

	if (Index == 1)
	{
		ShowDuration = 0.1f;
		AC->SetSound(SW_First);
	}

	GetWorld()->GetTimerManager().SetTimer(EffectHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			Decal_HandPrint->SetVisibility(true);
			AC->Play();
		}), ShowDuration, false);
}

#pragma endregion