// Copyright by 2026-1 WAP Game 2 team

#include "Component/Tutorial/TutorialComponent.h"
#include "Component/Interact/InteractComponent.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include "UI/Base/Tutorial/UI_Tutorial.h"
#include "Player/Character/EHPlayer.h"
#include <Components/WidgetComponent.h>
#include <Components/BoxComponent.h>

#pragma region Base

void UTutorialComponent::BeginPlay()
{
	Super::BeginPlay();

	auto* Comp_Widget = Owner->FindComponentByTag<UWidgetComponent>(FName("Tutorial"));
	Comp_Widget->SetVisibility(true);
	Comp_Widget->InitWidget();

	Comp_Interact = Owner->FindComponentByClass<UInteractComponent>();

	UI_Tutorial = Cast<UUI_Tutorial>(Comp_Widget->GetUserWidgetObject());
	UI_Tutorial->SetTargetKey(TargetKey);
	UI_Tutorial->SetTargetDescription(TargetDescription);

	TriggerBox = NewObject<UBoxComponent>(Owner.Get());
	TriggerBox->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	TriggerBox->SetWorldTransform(TriggerTrans);
	TriggerBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnTriggerBeginOverlap);
	TriggerBox->RegisterComponent();

	auto* FloorSub = GetWorld()->GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>();
	FloorSub->FloorChange_Reset.AddUObject(this, &ThisClass::HideTutorialWidget);
}

#pragma endregion

#pragma region Widget

void UTutorialComponent::ShowTutorialWidget()
{
	if (USaveManager::LoadData_Progression().Progression != TargetProgression)
	{
		return;
	}
	
	UI_Tutorial->ShowTutorialAnimation(true);

	if (Comp_Interact.IsValid())
	{
		Comp_Interact->ShowHighlight(true);
	}
	else
	{
		FTimerHandle HideHandle;
		GetWorld()->GetTimerManager().SetTimer(HideHandle, this, &ThisClass::HideTutorialWidget, WidgetDuration, false);
	}
}

void UTutorialComponent::HideTutorialWidget()
{
	if (USaveManager::LoadData_Progression().Progression == TargetProgression)
	{
		UI_Tutorial->ShowTutorialAnimation(false);
	}
	else
	{
		UI_Tutorial->HideWidget();
	}

	if (Comp_Interact.IsValid())
	{
		Comp_Interact->ShowHighlight(false);
	}
}

#pragma endregion

#pragma region Trigger

void UTutorialComponent::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OverlappedComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto* Player = Cast<AEHPlayer>(OtherActor);
	if (!IsValid(Player))
	{
		return;
	}

	ShowTutorialWidget();

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

#pragma endregion