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
	Timeline_FrontMove = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_FrontMove"));
	Timeline_RotateMove = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_RotateMove"));
}

void AAnomaly_Object_WChair::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat Update_LeftWheelSpin;
	Update_LeftWheelSpin.BindUFunction(this, "UpdateWheelSpin");
	Timeline_WheelSpin->AddInterpFloat(CV_WheelSpin, Update_LeftWheelSpin);

	FOnTimelineFloat Update_Move;
	Update_Move.BindUFunction(this, "UpdateMove");
	Timeline_FrontMove->AddInterpFloat(CV_Move, Update_Move);

	FOnTimelineEvent End_Move;
	End_Move.BindUFunction(this, "EndMove");
	Timeline_FrontMove->SetTimelineFinishedFunc(End_Move);

	FOnTimelineFloat Update_Rotate;
	Update_Rotate.BindUFunction(this, "UpdateRotate");
	Timeline_RotateMove->AddInterpFloat(CV_Rotate, Update_Rotate);

	FOnTimelineEvent End_Rotate;
	End_Rotate.BindUFunction(this, "EndRotate");
	Timeline_RotateMove->SetTimelineFinishedFunc(End_Rotate);
}

void AAnomaly_Object_WChair::Reset()
{
	Super::Reset();
	bIsFirstMove = true;
}

#pragma endregion

#pragma region Moving

void AAnomaly_Object_WChair::StartMove()
{
	WheelMovement = 1;
	Timeline_WheelSpin->PlayFromStart();
	Timeline_FrontMove->PlayFromStart();
}

void AAnomaly_Object_WChair::StartRotate()
{
	WheelMovement = 4;
	Timeline_WheelSpin->PlayFromStart();
	Timeline_RotateMove->PlayFromStart();
}

void AAnomaly_Object_WChair::UpdateWheelSpin(float Value)
{
	FRotator Target1 = OriginalWheelRotation;
	FRotator Target2 = OriginalWheelRotation;
	Target1.Pitch = (WheelMovement == 1 || WheelMovement == 3) ? Value : -1 * Value;
	Target2.Pitch = (WheelMovement == 1 || WheelMovement == 4) ? Value : -1 * Value;
	LeftWheel->SetRelativeRotation(Target1);
	RightWheel->SetRelativeRotation(Target2);
}

void AAnomaly_Object_WChair::UpdateMove(float Value)
{
	FVector NewLocation = bIsFirstMove ? FMath::Lerp(StartLocation1, EndLocation1, Value) : FMath::Lerp(StartLocation2, EndLocation2, Value);
	SetActorLocation(NewLocation);
}

void AAnomaly_Object_WChair::EndMove()
{
	if (bIsFirstMove)
	{
		OwnerAnomalyEvent->DispatchToObject<AAnomaly_Object_Door>(&AAnomaly_Object_Door::CloseDoor);
		bIsFirstMove = false;
		StartRotate();
	}
}

void AAnomaly_Object_WChair::UpdateRotate(float Value)
{
	FRotator NewRotation = FMath::Lerp(StartRotation, EndRotation, Value);
	SetActorRotation(NewRotation);
}

void AAnomaly_Object_WChair::EndRotate()
{
	StartMove();
}

#pragma endregion

#pragma region AI

void AAnomaly_Object_WChair::OnCrawlChildSpawnedHandler(ACrawlChild* SpawnedCrawlChild)
{
	SpawnedCrawlChild->WheelChairObjectRef = this;
}

#pragma endregion