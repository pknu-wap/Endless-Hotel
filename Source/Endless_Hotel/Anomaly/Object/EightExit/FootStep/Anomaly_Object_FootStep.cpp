// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Object/EightExit/FootStep/Anomaly_Object_FootStep.h"
#include <Components/AudioComponent.h>
#include <Components/DecalComponent.h>

#pragma region Base

AAnomaly_Object_FootStep::AAnomaly_Object_FootStep(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Decal_FootStep = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal_FootStep"));
	SetRootComponent(Decal_FootStep);
	Decal_FootStep->SetRelativeRotation(FRotator(90, 90, 0));

	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AC->SetupAttachment(RootComponent);
}

void AAnomaly_Object_FootStep::BeginPlay()
{
	Super::BeginPlay();

	DisappearFootStep();
}

#pragma endregion

#pragma region FootStep

void AAnomaly_Object_FootStep::DisappearFootStep()
{
	Color_FootStep = Decal_FootStep->DecalColor;

	GetWorld()->GetTimerManager().SetTimer(DisappearHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			constexpr float MinusValue = 0.02f;
			CurrentOpacity -= MinusValue;

			Color_FootStep.A = CurrentOpacity;
			Decal_FootStep->SetDecalColor(Color_FootStep);

			if (CurrentOpacity <= TargetOpacity)
			{
				Destroy();
			}
		}), 0.1f, true);
}

#pragma endregion