// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Ceiling/Anomaly_Object_Ceiling.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"

#pragma region Base

AAnomaly_Object_Ceiling::AAnomaly_Object_Ceiling(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Mesh_Default = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Default"));
	SetRootComponent(Mesh_Default);
	Mesh_Default->SetRelativeRotation(FRotator(0, 0, 90));

	Mesh_Ceiling = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Ceiling"));
	Mesh_Ceiling->SetupAttachment(RootComponent);

	Timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
}

void AAnomaly_Object_Ceiling::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat UpdateFunc;
	UpdateFunc.BindUFunction(this, FName("CeilingRotate"));
	Timeline->AddInterpFloat(Curve_CeilingRotate, UpdateFunc);
}

#pragma endregion

#pragma region Ceiling Rotate

void AAnomaly_Object_Ceiling::CeilingRotate(float Value)
{
	FRotator Target = Mesh_Ceiling->GetRelativeRotation();
	Target.Yaw = Value;

	Mesh_Ceiling->SetRelativeRotation(Target);
}

void AAnomaly_Object_Ceiling::PlayCeilingRotate()
{
	Timeline->PlayFromStart();
}

#pragma endregion