// Copyright by 2026-1 WAP Game 2 team

#include "Component/Tutorial/TutorialComponent.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "UI/Tutorial/UI_Tutorial.h"
#include <Components/WidgetComponent.h>
#include <Components/BoxComponent.h>

#pragma region Base

void UTutorialComponent::BeginPlay()
{
	Super::BeginPlay();

	Comp_Widget = Owner->FindComponentByTag<UWidgetComponent>(FName("Tutorial"));
	Comp_Widget->SetVisibility(true);
	Comp_Widget->InitWidget();

	UI_Tutorial = Cast<UUI_Tutorial>(Comp_Widget->GetUserWidgetObject());
	UI_Tutorial->SetTargetKey(TargetKey);
	UI_Tutorial->SetTargetDescription(TargetDescription);

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
	UI_Tutorial->ShowTutorialAnimation(true);

	FTimerHandle DisappearHandle;
	GetWorld()->GetTimerManager().SetTimer(DisappearHandle, this, &ThisClass::DisappearTutorialWidget, WidgetDuration, false);
}

void UTutorialComponent::DisappearTutorialWidget()
{
	FSaveData_Tutorial Data = USaveManager::LoadData_Tutorial();
	Data.bIsFirstPlay = false;

	USaveManager::SaveData_Tutorial(Data);

	UI_Tutorial->ShowTutorialAnimation(false);
}

#pragma endregion

#pragma region Trigger

void UTutorialComponent::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OverlappedComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ShowTutorialWidget();

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

#pragma endregion