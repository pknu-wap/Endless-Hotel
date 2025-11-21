// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Ceiling/Anomaly_Ceiling.h"
#include "Anomaly/Object/Ceiling/Anomaly_Object_Ceiling.h"
#include "Kismet/GameplayStatics.h"

#pragma region Activity

void AAnomaly_Ceiling::ActivateAnomaly_Implementation(uint8 Anomaly_ID)
{
	Super::ActivateAnomaly_Implementation(Anomaly_ID);

	switch (Anomaly_ID)
	{
	case 4:
		CeilingAction = ([](AAnomaly_Object_Ceiling* Ceiling) {Ceiling->PlayCeilingRotate(); });
		break;
	}

	StartCeilingAction();
}

#pragma endregion

#pragma region Door

void AAnomaly_Ceiling::StartCeilingAction()
{
	TArray<AActor*> FoundActors = LinkedObjects;

	TWeakObjectPtr<AAnomaly_Ceiling> Wrapper = this;
	FTimerHandle CeilingHandle;
	GetWorld()->GetTimerManager().SetTimer(CeilingHandle, [Wrapper, CeilingHandle, FoundActors]() mutable
		{
			for (auto* FoundActor : FoundActors)
			{
				auto* Ceiling = Cast<AAnomaly_Object_Ceiling>(FoundActor);
				Wrapper->CeilingAction(Ceiling);
			}
		}, 0.5f, false);
}

#pragma endregion