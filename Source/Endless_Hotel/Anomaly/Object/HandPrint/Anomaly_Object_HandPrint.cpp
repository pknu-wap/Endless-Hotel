// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/HandPrint/Anomaly_Object_HandPrint.h"
#include "Anomaly/Object/Light/Anomaly_Object_Light.h"
#include <Components/AudioComponent.h>
#include <Components/DecalComponent.h>
#include <Kismet/GameplayStatics.h>

#pragma region Base

bool AAnomaly_Object_HandPrint::bIsFirstHandPrint = true;

AAnomaly_Object_HandPrint::AAnomaly_Object_HandPrint(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Decal_HandPrint = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal_HandPrint"));
	SetRootComponent(Decal_HandPrint);
	Decal_HandPrint->SetRelativeRotation(FRotator(90, 0, 0));

	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AC->SetupAttachment(RootComponent);
}

#pragma endregion

#pragma region Cong

void AAnomaly_Object_HandPrint::ReserveCongCong()
{
	constexpr float FirstDuration = 2.1f;

	if (bIsFirstHandPrint)
	{
		bIsFirstHandPrint = false;

		AC->Sound = Sound_First;
		AC->Play();

		TurnOffLights();

		FTimerHandle FirstHandle;
		GetWorld()->GetTimerManager().SetTimer(FirstHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
			{
				Decal_HandPrint->SetVisibility(true);
			}), FirstDuration, false);

		return;
	}

	FTimerHandle DelayHandle;
	GetWorld()->GetTimerManager().SetTimer(DelayHandle, this, &ThisClass::ShowHandPrint, FirstDuration + HandPrintIndex * 0.1f, false);
}

void AAnomaly_Object_HandPrint::ShowHandPrint()
{
	Decal_HandPrint->SetVisibility(true);
	AC->Sound = Sound_Default;
	AC->Play();
}

void AAnomaly_Object_HandPrint::TurnOffLights()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAnomaly_Object_Light::StaticClass(), OUT FoundActors);

	for (auto* FoundActor : FoundActors)
	{
		auto* Light = Cast<AAnomaly_Object_Light>(FoundActor);
		Light->TurnLight(false);
	}
}

#pragma endregion