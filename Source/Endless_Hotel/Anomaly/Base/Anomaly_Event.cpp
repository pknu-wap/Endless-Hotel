// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Base/Anomaly_Event.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include "Player/Character/EHPlayer.h"
#include <Engine/GameInstance.h>
#include <Kismet/GameplayStatics.h>
#include <Components/BoxComponent.h>

#pragma region Base

AAnomaly_Event::AAnomaly_Event(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AnomalyID = -1;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAnomaly_Event::BeginPlay()
{
	Super::BeginPlay();
	TriggerBox->SetWorldTransform(Transform_TriggerBox);
}

#pragma endregion

#pragma region Anomaly

void AAnomaly_Event::StartAnomalyAction()
{
	for (auto* TargetActor : TargetAnomalyObjects)
	{
		if (!TargetActor->ExecuteAnomalies.Contains(AnomalyName)) 
		{
			continue;
		}

		AnomalyAction(TargetActor);
	}
}

#pragma endregion

#pragma region Verdicts

void AAnomaly_Event::SetVerdictMode(EAnomalyVerdictMode NewMode)
{
	auto* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();
	Sub->SetVerdictMode(NewMode); // VerdictMode Setting
}

#pragma endregion

#pragma region Activity

void AAnomaly_Event::SetAnomalyState()
{
	AnomalyName = static_cast<EAnomalyName>(AnomalyID);
	TargetAnomalyObjects.Empty();
	for (auto* FoundActor : LinkedObjects)
	{
		auto* AnomalyObject = Cast<AAnomaly_Object_Base>(FoundActor);
		
		if (!AnomalyObject->ExecuteAnomalies.Contains(AnomalyName)) 
		{
			continue;
		}

		AnomalyObject->SetSolvedFalse();
		TargetAnomalyObjects.Add(AnomalyObject);
	}
}

#pragma endregion

#pragma region StartType

void AAnomaly_Event::ActiveTrigger()
{
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	TriggerBox->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::OnTriggerBox);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTriggerBox);
}

void AAnomaly_Event::OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEHPlayer* Player = Cast<AEHPlayer>(OtherActor);
	if (!Player) return;
	StartAnomalyAction();
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAnomaly_Event::ScheduleAnomaly(float delay)
{
	FTimerHandle DelayHandle;
	GetWorld()->GetTimerManager().SetTimer(DelayHandle, FTimerDelegate::CreateWeakLambda(
		this,
		[this]()
		{
			StartAnomalyAction();
		}), delay, false);
}

#pragma endregion

#pragma region Verdict

void AAnomaly_Event::InteractSolveVerdict()
{
	//상호작용 기반 해결여부
	UGameSystem* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();
	bool bAllSolved = true;

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAnomaly_Object_Neapolitan::StaticClass(), FoundActors);

	for (auto* FoundActor : FoundActors)
	{
		if (!IsValid(FoundActor) || FoundActor->GetLevel() != this->GetLevel())
		{
			continue;
		}

		auto* AnomalyObject = Cast<AAnomaly_Object_Neapolitan>(FoundActor);
		if (!AnomalyObject->bSolved)
		{
			bAllSolved = false;
			break;
		}
	}
	bIsSolved = bAllSolved;
	Sub->SetIsAnomalySolved(bIsSolved);
}
#pragma endregion