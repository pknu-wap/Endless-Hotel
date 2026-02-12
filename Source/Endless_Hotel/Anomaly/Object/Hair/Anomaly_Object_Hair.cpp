// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/Hair/Anomaly_Object_Hair.h"
#include <Kismet/GameplayStatics.h>
#include <Materials/MaterialParameterCollection.h>
#include <Materials/MaterialParameterCollectionInstance.h>
#include <Components/StaticMeshComponent.h>
#include <Components/TimelineComponent.h>
#include <Components/BoxComponent.h>
#include <Curves/CurveFloat.h>
#include <TimerManager.h>


AAnomaly_Object_Hair::AAnomaly_Object_Hair(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	HairTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("HairTimeline"));
}

void AAnomaly_Object_Hair::BeginPlay()
{
	Super::BeginPlay();

	if (!HairTimeline || !Curve_HairOpacity)
	{
		return;
	}

	FOnTimelineFloat UpdateDelegate;
	UpdateDelegate.BindUFunction(this, FName("UpdateHair"));
	HairTimeline->AddInterpFloat(Curve_HairOpacity, UpdateDelegate);
}

void AAnomaly_Object_Hair::StartHair()
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (!Pawn) return;

		TArray<UStaticMeshComponent*> MeshComps;
		Pawn->GetComponents<UStaticMeshComponent>(MeshComps);

		for (auto* Comp : MeshComps)
		{
			if (Comp->GetName().Contains("StaticMesh"))
			{
				HairMesh = Comp;
				break;
			}
		}
		
	FTimerHandle HairTimer;
	GetWorld()->GetTimerManager().SetTimer(HairTimer, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			HairTimeline->PlayFromStart();
		}), ScheduleAnomaly, false);
}


void AAnomaly_Object_Hair::UpdateHair(float Value)
{
	auto* Inst = GetWorld()->GetParameterCollectionInstance(HairMPC);
	Inst->SetScalarParameterValue("MP_HairOpacity", Value);

	if (Curve_HairLocation)
	{
		const float Time = HairTimeline->GetPlaybackPosition();
		const float LocX = Curve_HairLocation->GetFloatValue(Time);

		FVector Loc = HairMesh->GetRelativeLocation();
		Loc.X = LocX;
		HairMesh->SetRelativeLocation(Loc);
	}
}
