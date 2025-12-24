#include "Anomaly/EightExit/Hair/Anomaly_Hair.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

AAnomaly_Hair::AAnomaly_Hair(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAnomaly_Hair::BeginPlay()
{
	Super::BeginPlay();

	// Timeline 설계
	if (Curve_HairOpacity)
	{
		FOnTimelineFloat UpdateDelegate;
		UpdateDelegate.BindUFunction(this, "UpdateHair");
		HairTimeline.AddInterpFloat(Curve_HairOpacity, UpdateDelegate);
	}

	// Timeline 종료 델리게이트
	FOnTimelineEvent FinishedDelegate;
	FinishedDelegate.BindUFunction(this, "HairFinished");
	HairTimeline.SetTimelineFinishedFunc(FinishedDelegate);
}

void AAnomaly_Hair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HairTimeline.TickTimeline(DeltaTime);
}

void AAnomaly_Hair::ActivateAnomaly(uint8 Anomaly_ID)
{
	Super::ActivateAnomaly(Anomaly_ID);

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

	if (!HairMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("[Hair] Mesh Not Found!"));
		return;
	}

	FTimerHandle H;
	GetWorld()->GetTimerManager().SetTimer(H, FTimerDelegate::CreateLambda([this]()
		{
			HairTimeline.PlayFromStart();
		}), StartDelay, false);
}

void AAnomaly_Hair::UpdateHair(float Value)
{
	auto* Inst = GetWorld()->GetParameterCollectionInstance(HairMPC);
	Inst->SetScalarParameterValue("MP_HairOpacity", Value);

	if (Curve_HairLocation)
	{
		float LocX = Curve_HairLocation->GetFloatValue(HairTimeline.GetPlaybackPosition());
		FVector Loc = HairMesh->GetRelativeLocation();
		Loc.X = LocX;
		HairMesh->SetRelativeLocation(Loc);
	}
}

void AAnomaly_Hair::HairFinished()
{
	UE_LOG(LogTemp, Warning, TEXT("[Hair] Finished"));
}
