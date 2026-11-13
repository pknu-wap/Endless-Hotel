// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/Acquire/ManualFragment/ManualFragment.h"
#include "GameSystem/SubSystem/AnomalyPoolSubsystem.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include "GameSystem/SubSystem/SteamSubsystem.h"
#include "UI/Base/Manual/UI_Manual_Rule.h"
#include <Components/WidgetComponent.h>

#pragma region Base

AManualFragment::AManualFragment(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Comp_Description = CreateDefaultSubobject<UWidgetComponent>(TEXT("Comp_Description"));
	Comp_Description->SetupAttachment(RootComponent);
}

void AManualFragment::BeginPlay()
{
	Super::BeginPlay();

	auto* UI_ManualRule = Cast<UUI_Manual_Rule>(Comp_Description->GetUserWidgetObject());
	UI_ManualRule->SetDescriptionText(Description);

	auto* PoolSubsystem = GetGameInstance()->GetSubsystem<UAnomalyPoolSubsystem>();
	if (PoolSubsystem->AnomalyRules.Contains(NewRule))
	{
		Destroy();
	}
	else
	{
		SetManualFragment();
		auto* VerdictSubsystem = GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();
		VerdictSubsystem->OnAnomalyStateChanged.AddUObject(this, &ThisClass::SetManualFragment);
	}
}

void AManualFragment::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	auto* VerdictSubsystem = GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();
	VerdictSubsystem->OnAnomalyStateChanged.RemoveAll(this);

	Super::EndPlay(EndPlayReason);
}

#pragma endregion

#pragma region Acquire

void AManualFragment::SaveAcquireData()
{
	auto* GameInstance = GetGameInstance();
	auto* Subsystem = GetGameInstance()->GetSubsystem<UAnomalyPoolSubsystem>();
	Subsystem->AddAnomalyRule(NewRule);

	if (bHasFakeRule)
	{
		Subsystem->AddFakeManualEntry(AppearAnomaly, FakeRule, NewRule);
	}

	if (Subsystem->IsCollectedAllRule())
	{
		auto* SteamSub = GameInstance->GetSubsystem<USteamSubsystem>();
		SteamSub->UnlockAchievement(EAchievementID::Manual);
	}
}

#pragma endregion

#pragma region Setting

void AManualFragment::SetManualFragment() const
{
	auto* Subsystem = GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();
	const bool bIsVisible = Subsystem->CurrentAnomalyID == AppearAnomaly;
	Object->SetVisibility(bIsVisible, true);
	if (bIsVisible)
	{
		Subsystem->SetHasAnomalyRule(true);
	}
}

#pragma endregion