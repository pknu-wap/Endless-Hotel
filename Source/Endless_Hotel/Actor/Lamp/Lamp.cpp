// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Lamp/Lamp.h"
#include <Components/PointLightComponent.h>

#pragma region Base

ALamp::ALamp(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SM_Lamp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Lamp"));
	SetRootComponent(SM_Lamp);

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(RootComponent);
}

void ALamp::BeginPlay()
{
	Super::BeginPlay();

	TurnLampLight(true);
}

void ALamp::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(LightHandle);

	Super::EndPlay(EndPlayReason);
}

#pragma endregion

#pragma region Lamp

void ALamp::TurnLampLight(bool bOn)
{
	PointLight->SetVisibility(bOn);

	const float RandomOn = FMath::RandRange(FlickerMin, FlickerMax);
	const float Duration = bOn ? RandomOn : FLICKER_DURATION;
	GetWorld()->GetTimerManager().SetTimer(LightHandle, FTimerDelegate::CreateUObject(this, &ThisClass::TurnLampLight, !bOn), Duration, false);
}

#pragma endregion