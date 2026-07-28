// Copyright by 2026-1 WAP Game 2 team

#include "Actor/ManualFragment/ManualFragment.h"
#include "Anomaly/Event/Anomaly_Event.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include <Components/TextRenderComponent.h>

#pragma region Base

AManualFragment::AManualFragment(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Component_TextWidget = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Component_ManualWidget"));
	Component_TextWidget->SetupAttachment(RootComponent);
}

void AManualFragment::BeginPlay()
{
	Super::BeginPlay();
	auto* Subsystem = GetGameInstance()->GetSubsystem<UGameSystem>();
	Subsystem->OnAnomalySpawned.AddDynamic(this, &ThisClass::SetManualFragment);
}

#pragma endregion

#pragma region RuleSetting

void AManualFragment::SetManualFragment()
{
	auto* Subsystem = GetGameInstance()->GetSubsystem<UGameSystem>();
	if (Subsystem->AnomalyRules.Contains(Rule))
	{
		Destroy();
		return;
	}
	if (Subsystem->CurrentAnomaly->AnomalyID == BoundAnomaly)
	{
		SetActorTransform(Placement);
	}
}

#pragma endregion

#pragma region Interact

void AManualFragment::Interact_Implementation(AEHCharacter* Interacter)
{
	Super::Interact_Implementation(Interacter);
	FInteractInfo Info = Component_Interact->GetSelectedInteractInfo();
	switch (Info.InteractType)
	{
	case EInteractType::Pick:
		auto* Subsystem = GetGameInstance()->GetSubsystem<UGameSystem>();
		Subsystem->AddAnomalyRule(Rule);
		Destroy();
		break;
	}
}

#pragma endregion