// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Event/Neapolitan/CrawlChild/Anomaly_CrawlChild.h"
#include "Anomaly/Object/Neapolitan/CrawlChild/Anomaly_Object_CrawlChild.h"
#include "Anomaly/Object/EightExit/Door/Anomaly_Object_Door.h"
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
		//SetupAnomalyAction<AAnomaly_CrawlChild>(&AAnomaly_CrawlChild::ShowSubTitle);
		SetupAnomalyAction<AAnomaly_Object_CrawlChild>(&AAnomaly_Object_CrawlChild::StartCrawlChild);
		//SetupAnomalyAction<AAnomaly_Object_Door>(&AAnomaly_Object_Door::OpenDoor);
		ActiveTrigger();
		break;
	}
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