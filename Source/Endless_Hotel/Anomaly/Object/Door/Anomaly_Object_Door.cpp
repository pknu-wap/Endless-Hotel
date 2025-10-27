// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Door/Anomaly_Object_Door.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"

#pragma region Base

AAnomaly_Object_Door::AAnomaly_Object_Door(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Mesh_Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Door"));
	SetRootComponent(Mesh_Door);

	Mesh_Handle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Handle"));
	Mesh_Handle->SetupAttachment(RootComponent);

	Timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));

	FOnTimelineFloat UpdateFunc;
	UpdateFunc.BindUFunction(this, FName("ShakeHandle"));
	Timeline->AddInterpFloat(Curve_HandleShake, UpdateFunc);

	FOnTimelineEvent FinishFunc;
	FinishFunc.BindUFunction(this, FName("PlayHandleShake"));
	Timeline->SetTimelineFinishedFunc(FinishFunc);
}

#pragma endregion

#pragma region Handle Shake

void AAnomaly_Object_Door::ShakeHandle(float Value)
{
	FVector Target = Mesh_Handle->GetRelativeLocation();
	Target.Z += Value;

	Mesh_Handle->SetRelativeLocation(Target);
}

void AAnomaly_Object_Door::PlayHandleShake()
{
	Timeline->PlayFromStart();
}

#pragma endregion