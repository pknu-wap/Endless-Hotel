// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Door/Anomaly_Door.h"
#include "Anomaly/Object/Door/Anomaly_Object_Door.h"
#include "Kismet/GameplayStatics.h"

#pragma region Base

// For test
AAnomaly_Door::AAnomaly_Door(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	DoorAction = ([](AAnomaly_Object_Door* Door)
		{
			Door->PlayHandleShake();
		});
}

// For test
void AAnomaly_Door::BeginPlay()
{
	Super::BeginPlay();

	ActivateAnomaly_Implementation();
}

#pragma endregion

#pragma region Activity

void AAnomaly_Door::ActivateAnomaly_Implementation()
{
	Super::ActivateAnomaly_Implementation();

	// 이 부분은 ID를 넘겨받는 부분이 생기면 바로 수정 예정
	/*switch (Anomaly_ID)
	{
		case ?:
			DoorAction = ([](AAnomaly_Object_Door* Door) {Door->PlayHandleShake(); });
		break;
	}*/

	StartDoorAction();
}

#pragma endregion

#pragma region Door

void AAnomaly_Door::StartDoorAction()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAnomaly_Object_Door::StaticClass(), OUT FoundActors);

	FTimerHandle LightHandle;
	GetWorld()->GetTimerManager().SetTimer(LightHandle, [this, LightHandle, FoundActors]() mutable
		{
			for (auto* FoundActor : FoundActors)
			{
				auto* Light = Cast<AAnomaly_Object_Door>(FoundActor);
				DoorAction(Light);
			}
		}, 0.5f, true);
}

#pragma endregion