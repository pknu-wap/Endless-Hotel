// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/EightExit/Hair/Anomaly_Object_Hair.h"
#include "Player/Character/EHPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "TimerManager.h"

AAnomaly_Object_Hair::AAnomaly_Object_Hair(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	HairTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("HairTimeline"));
}

void AAnomaly_Object_Hair::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat UpdateDelegate;
	UpdateDelegate.BindUFunction(this, FName("UpdateHair"));
	HairTimeline->AddInterpFloat(Curve_HairOpacity, UpdateDelegate);
}

void AAnomaly_Object_Hair::StartHair()
{
	bHairActive = true;
	FTimerHandle HairTimer;
	GetWorld()->GetTimerManager().SetTimer(
		HairTimer,
		FTimerDelegate::CreateWeakLambda(this, [this]()
			{
				SpawnHair();
				HairTimeline->PlayFromStart();
			}),
		ScheduleAnomaly,
		false
	);
}

void AAnomaly_Object_Hair::SpawnHair()
{
	if (SpawnedHairActor)
	{
		SpawnedHairActor->Destroy();
	}

	AEHPlayer* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	UCameraComponent* CameraComp = Player->GetCamera();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	SpawnedHairActor = GetWorld()->SpawnActor<AActor>(
		HairActorClass,
		CameraComp->GetComponentTransform(),
		SpawnParams
	);


	SpawnedHairActor->AttachToComponent(
		CameraComp,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale
	);

	SpawnedHairActor->SetActorRelativeLocation(HairRelativeLocation);
	SpawnedHairActor->SetActorRelativeRotation(HairRelativeRotation);

	HairMesh = SpawnedHairActor->FindComponentByClass<UStaticMeshComponent>();

	HairMesh->SetSimulatePhysics(false);
	HairMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	InitialHairLocation = HairMesh->GetRelativeLocation();
}

void AAnomaly_Object_Hair::UpdateHair(float Value)
{
	UMaterialParameterCollectionInstance* Inst = GetWorld()->GetParameterCollectionInstance(HairMPC);
	Inst->SetScalarParameterValue(Param_Opacity, Value);

	if (Curve_HairLocation)
	{
		const float Time = HairTimeline->GetPlaybackPosition();
		const float LocX = Curve_HairLocation->GetFloatValue(Time);

		FVector Loc = InitialHairLocation;
		Loc.X = LocX;
		HairMesh->SetRelativeLocation(Loc);
	}
}

void AAnomaly_Object_Hair::ResetHair(bool bIsStart)
{
	UMaterialParameterCollectionInstance* Inst = GetWorld()->GetParameterCollectionInstance(HairMPC);
	if (Inst)
	{
		Inst->SetScalarParameterValue(Param_Opacity, 0.0f);
	}

	if (SpawnedHairActor)
	{
		SpawnedHairActor->Destroy();
		SpawnedHairActor = nullptr;
	}

	HairMesh = nullptr;
	bHairActive = false;
}

void AAnomaly_Object_Hair::Reset()
{
	Super::Reset();

	if (!bHairActive && !SpawnedHairActor)
	{
		return;
	}

	if (HairTimeline)
	{
		HairTimeline->Stop();
	}

	ResetHair(false);
}