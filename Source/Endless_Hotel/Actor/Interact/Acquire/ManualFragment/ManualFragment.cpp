// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/Acquire/ManualFragment/ManualFragment.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include <Components/TextRenderComponent.h>

#pragma region Base

AManualFragment::AManualFragment(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Comp_Description = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Comp_Description"));
	Comp_Description->SetupAttachment(RootComponent);
}

void AManualFragment::BeginPlay()
{
	Super::BeginPlay();

	auto* Subsystem = GetGameInstance()->GetSubsystem<UGameSystem>();
	if (Subsystem->AnomalyRules.Contains(NewRule))
	{
		Destroy();
	}
	else
	{
		Subsystem->OnAnomalySpawned.AddDynamic(this, &ThisClass::SetManualFragment);
	}
}

#pragma endregion

#pragma region Acquire

void AManualFragment::SaveAcquireData()
{
	auto* Subsystem = GetGameInstance()->GetSubsystem<UGameSystem>();
	Subsystem->AddAnomalyRule(NewRule);
}

#pragma endregion

#pragma region Setting

void AManualFragment::SetManualFragment()
{
	auto* Subsystem = GetGameInstance()->GetSubsystem<UGameSystem>();
	Object->SetVisibility(Subsystem->CurrentAnomalyID == AppearAnomaly, true);
}

#pragma endregion