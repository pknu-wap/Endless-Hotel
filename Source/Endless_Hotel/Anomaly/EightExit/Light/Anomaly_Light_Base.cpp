// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Light/Anomaly_Light_Base.h"
#include "Anomaly/Object/Light/Anomaly_Object_Light.h"
#include "Kismet/GameplayStatics.h"

#pragma region Base

void AAnomaly_Light_Base::BeginPlay()
{
	Super::BeginPlay();

	ActivateAnomaly_Implementation();
}

#pragma endregion

#pragma region Activity

void AAnomaly_Light_Base::ActivateAnomaly_Implementation()
{
	Super::ActivateAnomaly_Implementation();

	StartLightAction(LightAction);
}

#pragma endregion

#pragma region Light

void AAnomaly_Light_Base::StartLightAction(TFunction<void(AAnomaly_Object_Light*)> Action)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAnomaly_Object_Light::StaticClass(), OUT FoundActors);

	FTimerHandle LightHandle;
	GetWorld()->GetTimerManager().SetTimer(LightHandle, [this, LightHandle, FoundActors, Action]() mutable
		{
			for (auto* FoundActor : FoundActors)
			{
				auto* Light = Cast<AAnomaly_Object_Light>(FoundActor);
				if (CurrentIndex == Light->LightIndex)
				{
					Action(Light);
				}
			}

			if (++CurrentIndex > MaxIndex)
			{
				GetWorld()->GetTimerManager().ClearTimer(LightHandle);
			}
		}, 0.5f, true);
}

#pragma endregion