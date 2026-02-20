// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/EightExit/Ceiling/Anomaly_Object_Ceiling.h"
#include <Components/StaticMeshComponent.h>
#include <Components/TimelineComponent.h>
#include <Niagara/Public/NiagaraComponent.h>

#pragma region Base

AAnomaly_Object_Ceiling::AAnomaly_Object_Ceiling(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Mesh_Ceiling = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Ceiling"));
	Mesh_Ceiling->SetupAttachment(RootComponent);

	Niagara_Ceiling_Blood = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara_Ceiling_Blood"));
	Niagara_Ceiling_Blood->SetupAttachment(RootComponent);
	Niagara_Ceiling_Blood->SetAutoActivate(false);

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

#pragma region Ceiling Blood

void AAnomaly_Object_Ceiling::CeilingBloodDripping()
{
	Niagara_Ceiling_Blood->SetActive(true);
}

#pragma endregion
