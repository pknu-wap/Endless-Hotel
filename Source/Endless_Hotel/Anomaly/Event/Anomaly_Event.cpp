// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/Anomaly_Event.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include "Player/Character/EHPlayer.h"
#include <Engine/GameInstance.h>
#include <Kismet/GameplayStatics.h>
#include <Components/BoxComponent.h>
#include <EngineUtils.h>

#pragma region Base

AAnomaly_Event::AAnomaly_Event(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAnomaly_Event::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->SetWorldTransform(TriggerBox_Transform);

	auto* SubSystem = GetGameInstance()->GetSubsystem<UGameSystem>();
	SubSystem->FloorChange_Disable.AddUniqueDynamic(this, &ThisClass::DisableAnomaly);
}

#pragma endregion

#pragma region Anomaly

void AAnomaly_Event::StartAnomalyAction()
{
	for (const auto& Action : AnomalyActions)
	{
		Action(this);
	}

	for (UObject* TargetObj : TargetAnomalyObjects)
	{
		if (AAnomaly_Object_Base* AnomalyObj = Cast<AAnomaly_Object_Base>(TargetObj))
		{
			if (!AnomalyObj->ExecuteAnomalies.Contains(AnomalyID))
			{
				continue;
			}
		}
		for (const auto& Action : AnomalyActions)
		{
			Action(TargetObj);
		}
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
	TargetAnomalyObjects.Empty();
	for (auto* FoundActor : LinkedObjects)
	{
		auto* AnomalyObject = Cast<AAnomaly_Object_Base>(FoundActor);
		
		if (!AnomalyObject->ExecuteAnomalies.Contains(AnomalyID)) 
		{
			continue;
		}

		if(!bIsEightExit && !AnomalyObject->bIsEightExitObject)
		{
			AnomalyObject->SetSolvedFalse();
		}

		TargetAnomalyObjects.Add(AnomalyObject);
	}
}

void AAnomaly_Event::DisableAnomaly()
{
	this->LinkedObjects.Empty();
	this->TargetAnomalyObjects.Empty();
	this->Destroy();
}

#pragma endregion

#pragma region StartType

void AAnomaly_Event::ActiveTrigger()
{
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	TriggerBox->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::OnTriggerBox);
	TriggerBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnTriggerBox);
}

void AAnomaly_Event::OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEHPlayer* Player = Cast<AEHPlayer>(OtherActor);
	if (!Player) return;
	StartAnomalyAction();
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAnomaly_Event::ScheduleAnomaly(float Delay)
{
	FTimerHandle DelayHandle;
	GetWorld()->GetTimerManager().SetTimer(DelayHandle, FTimerDelegate::CreateWeakLambda(
		this,
		[this]()
		{
			StartAnomalyAction();
		}), Delay, false);
}

#pragma endregion

#pragma region Verdict

void AAnomaly_Event::InteractSolveVerdict()
{
	UGameSystem* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();
	bool bAllSolved = true;

	for (const auto& AnomalyObject : TargetAnomalyObjects)
	{
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