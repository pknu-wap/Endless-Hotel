#include "Anomaly/EightExit/Hair/Anomaly_Hair.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"

AAnomaly_Hair::AAnomaly_Hair(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->InitBoxExtent(FVector(100, 100, 100));
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAnomaly_Hair::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->SetWorldLocation(FVector(-1800.f, 580.f, 680.f));

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
		float LocX = Curve_HairLocation->GetFloatValue(HairTimeline.GetPlaybackPosition());
		FVector Loc = HairMesh->GetRelativeLocation();
		Loc.X = LocX;
		HairMesh->SetRelativeLocation(Loc);
	}
}

#pragma region Trigger

void AAnomaly_Hair::ActiveTrigger()
{
	Super::ActiveTrigger();

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	TriggerBox->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::OnTriggerBeginOverlap);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTriggerBeginOverlap);
}

void AAnomaly_Hair::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FTimerHandle H;
	GetWorld()->GetTimerManager().SetTimer(H, FTimerDelegate::CreateLambda([this]()
		{
			HairTimeline.PlayFromStart();
		}), StartDelay, false);

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

#pragma endregion