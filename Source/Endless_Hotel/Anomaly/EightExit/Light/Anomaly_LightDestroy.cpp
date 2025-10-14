// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Light/Anomaly_LightDestroy.h"
#include "Anomaly/Object/Light/Anomaly_Object_Light.h"
#include "Kismet/GameplayStatics.h"

#pragma region Base

void AAnomaly_LightDestroy::BeginPlay()
{
	Super::BeginPlay();

	ActivateAnomaly_Implementation(); // 임시 코드 - 테스트용
}

#pragma endregion

#pragma region Activity

void AAnomaly_LightDestroy::ActivateAnomaly_Implementation()
{
	Super::ActivateAnomaly_Implementation();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAnomaly_Object_Light::StaticClass(), OUT FoundActors);

	FTimerHandle LightHandle;
	GetWorld()->GetTimerManager().SetTimer(LightHandle, [this, LightHandle, FoundActors]() mutable
		{
			for (auto* FoundActor : FoundActors)
			{
				auto* Light = Cast<AAnomaly_Object_Light>(FoundActor);
				if (CurrentIndex == Light->LightIndex)
				{
					Light->DropLight();
				}
			}

			if (++CurrentIndex > MaxIndex)
			{
				GetWorld()->GetTimerManager().ClearTimer(LightHandle);
			}
		}, 0.5f, true);
}

#pragma endregion