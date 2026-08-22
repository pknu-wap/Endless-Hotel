// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Event/EightExit/CrawlChild/Anomaly_CrawlChild.h"
#include "Character/AI/CrawlChild/CrawlChildController.h"
#include "Anomaly/Object/EightExit/CrawlChild/Anomaly_Object_CrawlChild.h"
#include "Anomaly/Object/EightExit/CrawlChild/AAnomaly_Object_WChair.h"
#include "Anomaly/Object/EightExit/Door/Anomaly_Object_Door.h"
#include "Anomaly/Object/EightExit/Ceiling/Anomaly_Object_Ceiling.h"
#include "Character/AI/CrawlChild/CrawlChild.h"
#include "Player/Controller/EHPlayerController.h"
#include "UI/Controller/UI_Controller.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>

#pragma region CrawlChild

void AAnomaly_CrawlChild::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyID)
	{
	case EAnomalyID::CrawlChild:
		SetupAnomalyAction<AAnomaly_Object_CrawlChild>(&AAnomaly_Object_CrawlChild::SetupCrawlChildObject);
		SetupAnomalyAction<ThisClass>(&ThisClass::StartCrawlChild);
		SetupAnomalyAction<AAnomaly_Object_Ceiling>(&AAnomaly_Object_Ceiling::SetupCrawlChildCeilingObject);
		SetupAnomalyAction<AAnomaly_Object_Door>(&AAnomaly_Object_Door::OpenDoor);
		SetupAnomalyAction<AAnomaly_Object_WChair>(&AAnomaly_Object_WChair::StartMove);
		ActiveTrigger();
		break;
	}
}

#pragma endregion

#pragma region Anomaly

void AAnomaly_CrawlChild::DisableAnomaly()
{
	CrawlChild->Destroy();
	Super::DisableAnomaly();
}

#pragma endregion

#pragma region Subtitle

void AAnomaly_CrawlChild::ShowSubTitle()
{
	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	FTimerHandle SubTitleTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(SubTitleTimerHandle, FTimerDelegate::CreateWeakLambda(this, [this, UICon]()
		{
			uint8 SubtitleIndex = FMath::RandRange(0, Subtitle.Num() - 1);
			UICon->ShowSubTitle(Subtitle[SubtitleIndex], 2, 0.5f);
		}), 2, true);
}

#pragma endregion

#pragma region AI

void AAnomaly_CrawlChild::StartCrawlChild()
{
	CrawlChild = GetWorld()->SpawnActor<ACrawlChild>(CrawlChildClass, AIStartTransform);
	CrawlChild->SetOwnerAnomalyEvent(this);
	DispatchToObject<AAnomaly_Object_WChair>(&AAnomaly_Object_WChair::OnCrawlChildSpawnedHandler, CrawlChild.Get());
	DispatchToObject<AAnomaly_Object_CrawlChild>(&AAnomaly_Object_CrawlChild::OnCrawlChildSpawnedHandler, CrawlChild.Get());
	ACrawlChildController* CrawlChildController = Cast<ACrawlChildController>(CrawlChild->GetController());
	CrawlChildController->StartWithWheelChair();
}

#pragma endregion