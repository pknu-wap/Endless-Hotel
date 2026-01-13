// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Hair/Anomaly_Hair.h"
#include <Kismet/GameplayStatics.h>
#include <Materials/MaterialParameterCollection.h>
#include <Materials/MaterialParameterCollectionInstance.h>
#include <Components/StaticMeshComponent.h>
#include <Components/TimelineComponent.h>
#include <Components/BoxComponent.h>
#include <Curves/CurveFloat.h>
#include <TimerManager.h>

AAnomaly_Hair::AAnomaly_Hair(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	HairTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("HairTimeline"));

	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->InitBoxExtent(FVector(100, 100, 100));
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAnomaly_Hair::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->SetWorldLocation(FVector(-1800.f, 580.f, 680.f));

	if (!HairTimeline || !Curve_HairOpacity)
	{
		return;
	}

	FOnTimelineFloat UpdateDelegate;
	UpdateDelegate.BindUFunction(this, FName("UpdateHair"));
	HairTimeline->AddInterpFloat(Curve_HairOpacity, UpdateDelegate);
}

void AAnomaly_Hair::ActivateAnomaly()
{
	Super::ActivateAnomaly();

	ActiveTrigger();

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
}

void AAnomaly_Hair::UpdateHair(float Value)
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

#pragma region Trigger

void AAnomaly_Hair::ActiveTrigger()
{
	Super::ActiveTrigger();

	TriggerBox->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::OnTriggerBeginOverlap);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTriggerBeginOverlap);
}

void AAnomaly_Hair::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FTimerHandle HairTimer;
	GetWorld()->GetTimerManager().SetTimer(HairTimer, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			HairTimeline->PlayFromStart();
		}), StartDelay, false);

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

#pragma endregion