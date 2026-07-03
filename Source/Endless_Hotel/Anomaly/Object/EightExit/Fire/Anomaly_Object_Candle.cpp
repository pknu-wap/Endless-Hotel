// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/EightExit/Fire/Anomaly_Object_Candle.h"
#include <Components/AudioComponent.h>

#pragma region Base

AAnomaly_Object_Candle::AAnomaly_Object_Candle(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Comp_Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Comp_Audio"));
	Comp_Audio->SetupAttachment(Object);
}

#pragma endregion

#pragma region Reset

void AAnomaly_Object_Candle::Reset()
{
	Object->SetSimulatePhysics(false);
	Object->SetEnableGravity(false);

	Super::Reset();
}

#pragma endregion

#pragma region Fall

void AAnomaly_Object_Candle::FallCandle()
{
	Object->SetSimulatePhysics(true);
	Object->SetEnableGravity(true);
	Object->AddImpulse(ImpulseDirection.GetSafeNormal() * ImpulseStrength);
	Object->SetNotifyRigidBodyCollision(true);
	Object->OnComponentHit.AddUniqueDynamic(this, &ThisClass::OnCandleDropped);
}

void AAnomaly_Object_Candle::OnCandleDropped(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Comp_Audio->Play();

	Object->SetNotifyRigidBodyCollision(false);
	Object->OnComponentHit.Clear();
}

#pragma endregion