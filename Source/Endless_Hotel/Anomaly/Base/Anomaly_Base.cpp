// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Base/Anomaly_Base.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Player/Character/EHPlayer.h"
#include <Engine/GameInstance.h>
#include <Kismet/GameplayStatics.h>
#include <Components/BoxComponent.h>

#pragma region Base

AAnomaly_Base::AAnomaly_Base(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AnomalyID = -1;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAnomaly_Base::BeginPlay()
{
	Super::BeginPlay();
	TriggerBox->SetWorldTransform(Transform_TriggerBox);
}

#pragma endregion

#pragma region Anomaly

void AAnomaly_Base::StartAnomalyAction()
{
	for (auto* FoundActor : LinkedObjects)
	{
		auto* AnomalyObject = Cast<AAnomaly_Object_Base>(FoundActor);
		AnomalyAction(AnomalyObject);
	}
}

#pragma endregion

#pragma region Verdicts

void AAnomaly_Base::SetVerdictMode(EAnomalyVerdictMode NewMode)
{
	auto* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
	Sub->SetVerdictMode(NewMode); // VerdictMode Setting
}

#pragma endregion

#pragma region StartType

void AAnomaly_Base::ActiveTrigger()
{
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	TriggerBox->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::OnTriggerBox);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTriggerBox);
}

void AAnomaly_Base::OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEHPlayer* Player = Cast<AEHPlayer>(OtherActor);
	if (!Player) return;
	StartAnomalyAction();
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAnomaly_Base::StartDelay(float delay)
{
	FTimerHandle DelayHandle;
	GetWorld()->GetTimerManager().SetTimer(DelayHandle, FTimerDelegate::CreateWeakLambda(
		this,
		[this]()
		{
			StartAnomalyAction();
		}), delay, false);
}

void AAnomaly_Base::StartImmediate()
{
	StartAnomalyAction();
}

#pragma endregion