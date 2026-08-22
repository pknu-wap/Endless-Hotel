// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Object/EightExit/CrawlChild/AAnomaly_Object_WChair.h"
#include "Anomaly/Object/EightExit/Door/Anomaly_Object_Door.h"
#include "Anomaly/Event/EightExit/CrawlChild/Anomaly_CrawlChild.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include "Character/AI/CrawlChild/CrawlChild.h"
#include <Components/TimelineComponent.h>

#pragma region Base

AAnomaly_Object_WChair::AAnomaly_Object_WChair(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	LeftWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftWheel"));
	LeftWheel->SetupAttachment(RootComponent);
	RightWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightWheel"));
	RightWheel->SetupAttachment(RootComponent);

	Timeline_WheelSpin = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_WheelSpin"));
	Timeline_Move = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_Move"));
}

void AAnomaly_Object_WChair::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat Update_WheelSpin;
	Update_WheelSpin.BindUFunction(this, "UpdateWheelSpin");
	Timeline_WheelSpin->AddInterpFloat(CV_WheelSpin, Update_WheelSpin);

	FOnTimelineFloat Update_Move;
	Update_Move.BindUFunction(this, "UpdateMove");
	Timeline_Move->AddInterpFloat(CV_Move, Update_Move);

	FOnTimelineEvent End_Move;
	End_Move.BindUFunction(this, "EndMove");
	Timeline_Move->SetTimelineFinishedFunc(End_Move);
}

#pragma endregion

#pragma region Moving

void AAnomaly_Object_WChair::StartMove()
{
	Timeline_WheelSpin->PlayFromStart();
	Timeline_Move->PlayFromStart();
}

void AAnomaly_Object_WChair::UpdateWheelSpin(float Value)
{
	FRotator Target1 = OriginalWheelRotation;
	FRotator Target2 = OriginalWheelRotation;
	Target1.Pitch = Value;
	Target2.Pitch = Value;
	LeftWheel->SetRelativeRotation(Target1);
	RightWheel->SetRelativeRotation(Target2);
}

void AAnomaly_Object_WChair::UpdateMove(float Value)
{
	FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, Value);
	SetActorLocation(NewLocation);
}

void AAnomaly_Object_WChair::EndMove()
{
	OwnerAnomalyEvent->DispatchToObject<AAnomaly_Object_Door>(&AAnomaly_Object_Door::CloseDoor);
}

#pragma endregion

#pragma region AI

void AAnomaly_Object_WChair::OnCrawlChildSpawnedHandler(ACrawlChild* SpawnedCrawlChild)
{
	SpawnedCrawlChild->WheelChairObjectRef = this;
}

#pragma endregion