// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/EightExit/Ceiling/Anomaly_Object_Ceiling.h"
#include "Anomaly/Event/EightExit/CrawlChild/Anomaly_CrawlChild.h"
#include "Character/AI/CrawlChild/CrawlChild.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include <Components/StaticMeshComponent.h>
#include <Components/TimelineComponent.h>
#include <Components/BoxComponent.h>
#include <Niagara/Public/NiagaraComponent.h>
#include <GeometryCollection/GeometryCollectionComponent.h>
#include <Field/FieldSystemObjects.h>

#pragma region Base

AAnomaly_Object_Ceiling::AAnomaly_Object_Ceiling(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Niagara_Ceiling_Blood = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara_Ceiling_Blood"));
	Niagara_Ceiling_Blood->SetupAttachment(RootComponent);
	Niagara_Ceiling_Blood->SetAutoActivate(false);

	Timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
	GeometryCollection_Ceiling = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GeometryCollection_Ceiling"));
	GeometryCollection_Ceiling->SetupAttachment(RootComponent);
}

void AAnomaly_Object_Ceiling::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat UpdateFunc;
	UpdateFunc.BindUFunction(this, FName("CeilingRotate"));
	Timeline->AddInterpFloat(Curve_CeilingRotate, UpdateFunc);
}

void AAnomaly_Object_Ceiling::Reset()
{
	Super::Reset();
	Timeline->Stop();
	Timeline->SetNewTime(0.f);
	Niagara_Ceiling_Blood->Deactivate();
	Niagara_Ceiling_Blood->SetVisibility(false);
	Object->SetVisibility(true);
	GetWorld()->GetTimerManager().ClearTimer(BloodHandle);
	bHasCollapsed = false;
	if (ActiveCollapseFieldWeak.IsValid())
	{
		ActiveCollapseFieldWeak->Destroy();
	}
	ActiveCollapseFieldWeak = nullptr;
	GeometryCollection_Ceiling->SetVisibility(false);
	GeometryCollection_Ceiling->SetSimulatePhysics(false);
}

#pragma endregion

#pragma region Ceiling Rotate

void AAnomaly_Object_Ceiling::CeilingRotate(float Value)
{
	FRotator Target = GetActorRotation();
	Target.Pitch = Value;
	SetActorRotation(Target);
}

void AAnomaly_Object_Ceiling::PlayCeilingRotate()
{
	Timeline->PlayFromStart();
}

#pragma endregion

#pragma region Ceiling Blood

void AAnomaly_Object_Ceiling::CeilingBloodDripping()
{
	Niagara_Ceiling_Blood->SetVisibility(true);
	Niagara_Ceiling_Blood->Activate(true);

	GetWorld()->GetTimerManager().SetTimer(BloodHandle, FTimerDelegate::CreateWeakLambda(this, [this]
		{
			FVector Size1 = BloodLocationMax1 - BloodLocationMin1;
			FVector Size2 = BloodLocationMax2 - BloodLocationMin2;
			float Volume1 = Size1.X * Size1.Y * 1;
			float Volume2 = Size2.X * Size2.Y * 1;
			float TotalVolume = Volume1 + Volume2;
			FVector RandomLocation = FMath::FRandRange(0.f, TotalVolume) < Volume1 ?
				FVector(
					FMath::FRandRange(BloodLocationMin1.X, BloodLocationMax1.X),
					FMath::FRandRange(BloodLocationMin1.Y, BloodLocationMax1.Y),
					FMath::FRandRange(BloodLocationMin1.Z, BloodLocationMax1.Z)
				) :
				FVector(
					FMath::FRandRange(BloodLocationMin2.X, BloodLocationMax2.X),
					FMath::FRandRange(BloodLocationMin2.Y, BloodLocationMax2.Y),
					FMath::FRandRange(BloodLocationMin2.Z, BloodLocationMax2.Z)
				);
			Niagara_Ceiling_Blood->SetRelativeLocation(RandomLocation);
		}
	), BloodInterval, true);
}

#pragma endregion

#pragma region Ceiling_Collapse

void AAnomaly_Object_Ceiling::TriggerCeilingCollapse()
{
	if (bHasCollapsed) 
	{
		return;
	}
	FVector CeilingLocation = GeometryCollection_Ceiling->GetComponentLocation();
	float Radius = 100000.f;
	int32 PropagationDepth = 0;
	float PropagationFactor = 0.f;
	float Strain = 999999.f;

	GeometryCollection_Ceiling->ApplyExternalStrain(0, CeilingLocation, Radius, PropagationDepth, PropagationFactor, Strain);
	GeometryCollection_Ceiling->WakeAllRigidBodies();
	bHasCollapsed = true;
}

void AAnomaly_Object_Ceiling::SetupCrawlChildCeilingObject()
{
	Object->SetVisibility(false);
	GeometryCollection_Ceiling->SetSimulatePhysics(true);
	GeometryCollection_Ceiling->SetVisibility(true);
}

#pragma endregion