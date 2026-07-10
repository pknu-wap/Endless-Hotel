// Copyright by 2026-1 WAP Game 2 team

#include "Component/Tutorial/TutorialComponent.h"
#include "Component/Interact/InteractComponent.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "UI/Base/Tutorial/UI_Tutorial.h"
#include <Components/WidgetComponent.h>
#include <Components/BoxComponent.h>

#pragma region Base

void UTutorialComponent::BeginPlay()
{
	Super::BeginPlay();

	Comp_Widget = Owner->FindComponentByTag<UWidgetComponent>(FName("Tutorial"));
	Comp_Widget->SetVisibility(true);
	Comp_Widget->InitWidget();

	Comp_Interact = Owner->FindComponentByClass<UInteractComponent>();

	UI_Tutorial = Cast<UUI_Tutorial>(Comp_Widget->GetUserWidgetObject());
	UI_Tutorial->SetTargetKey(TargetKey);
	UI_Tutorial->SetTargetDescription(TargetDescription);

	auto* GameSystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSystem>();
	GameSystem->FloorChange_Reset.AddUniqueDynamic(this, &ThisClass::HideTutorialWidget);

	FSaveData_Tutorial Data = USaveManager::LoadData_Tutorial();

	if (!Data.bIsFirstPlay)
	{
		return;
	}

	TriggerBox = NewObject<UBoxComponent>(Owner.Get());
	TriggerBox->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	TriggerBox->SetWorldTransform(TriggerTrans);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTriggerBeginOverlap);
	TriggerBox->RegisterComponent();
}

#pragma endregion

#pragma region Widget

void UTutorialComponent::ShowTutorialWidget()
{
	if (!USaveManager::LoadData_Tutorial().bIsFirstPlay)
	{
		return;
	}

	UI_Tutorial->ShowTutorialAnimation(true);

	if (Comp_Interact.IsValid())
	{
		Comp_Interact->ShowInteractingHighlight(true);
	}
	else
	{
		FTimerHandle HideHandle;
		GetWorld()->GetTimerManager().SetTimer(HideHandle, this, &ThisClass::HideTutorialWidget, 10.f, false);
	}
}

void UTutorialComponent::HideTutorialWidget()
{
	FSaveData_Tutorial Data = USaveManager::LoadData_Tutorial();
	Data.bIsFirstPlay = false;

	USaveManager::SaveData_Tutorial(Data);

	if (UI_Tutorial.IsValid())
	{
		if (Data.bIsFirstPlay)
		{
			UI_Tutorial->ShowTutorialAnimation(false);
		}
		else
		{
			UI_Tutorial->HideWidget();
		}
	}

	if (Comp_Interact.IsValid())
	{
		Comp_Interact->ShowInteractingHighlight(false);
	}
}

#pragma endregion

#pragma region Trigger

void UTutorialComponent::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OverlappedComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ShowTutorialWidget();

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

#pragma endregion