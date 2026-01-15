// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Anomaly_Object_Neapolitan.h"
#include "UI/World/Interact/UI_Interact.h"
#include "Component/LookAt/LookAtComponent.h"
#include <Components/WidgetComponent.h>


#pragma region Base

AAnomaly_Object_Neapolitan::AAnomaly_Object_Neapolitan(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void AAnomaly_Object_Neapolitan::BeginPlay()
{
	Super::BeginPlay();
	bSolved = false;
	if (!WC) return;
	UI_Interact = Cast<UUI_Interact>(WC->GetUserWidgetObject());
	UI_Interact->SetDescription(DescriptionText);
	LAC->SettingWidgetComponent(WC);

	OriginalTransform = GetActorTransform();
}

#pragma endregion

#undef LOCTEXT_NAMESPACE

#pragma region Interact

void AAnomaly_Object_Neapolitan::Interacted_Implementation()
{
	StartInteractaction();
}

void AAnomaly_Object_Neapolitan::ShowInteractWidget_Implementation(bool bIsShow)
{
	UI_Interact->ShowDescription(bIsShow);
}

void AAnomaly_Object_Neapolitan::StartInteractaction()
{
	InteractAction();
}

#pragma endregion