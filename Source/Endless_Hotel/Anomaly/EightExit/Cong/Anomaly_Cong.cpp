// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Cong/Anomaly_Cong.h"
#include "Anomaly/Object/HandPrint/Anomaly_Object_HandPrint.h"
#include "Components/BoxComponent.h"

#pragma region Base

AAnomaly_Cong::AAnomaly_Cong(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTriggerBox);
}

void AAnomaly_Cong::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->SetWorldTransform(Transform_TriggerBox);
}

#pragma endregion

#pragma region Trigger

void AAnomaly_Cong::OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	StartAnomalyAction();

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

#pragma endregion

#pragma region Cong

void AAnomaly_Cong::StartAnomalyAction()
{
	CongDelegate = FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			TArray<AActor*> RemoveTargets;

			for (auto* FoundActor : LinkedObjects)
			{
				auto* HandPrint = Cast<AAnomaly_Object_HandPrint>(FoundActor);

				if (CurrentIndex == HandPrint->HandPrintIndex)
				{
					HandPrint->StartCongCong(NextCong);
					RemoveTargets.Add(FoundActor);
				}
			}

			for (auto* RemoveTarget : RemoveTargets)
			{
				LinkedObjects.Remove(RemoveTarget);
			}

			if (CurrentIndex >= MaxIndex)
			{
				GetWorld()->GetTimerManager().ClearTimer(CongHandle);
				return;
			}

			CurrentIndex++;
			GetWorld()->GetTimerManager().SetTimer(CongHandle, CongDelegate, NextCong, false);
		});

	GetWorld()->GetTimerManager().SetTimer(CongHandle, CongDelegate, 0.01f, false);

	AAnomaly_Object_HandPrint::bIsFirstHandPrint = true;
}

#pragma endregion