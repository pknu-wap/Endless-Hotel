// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/Anomaly_Object_Neapolitan.h"
#include "Components/WidgetComponent.h"
#include "UI/Base/InGame/Interact/UI_Interact.h"
#include "Component/LookAt/LookAtComponent.h"

#define LOCTEXT_NAMESPACE "Anomaly_Object_Neapolitan"

#pragma region Base


AAnomaly_Object_Neapolitan::AAnomaly_Object_Neapolitan(const FObjectInitializer& ObjectInitializer)
{
	Object = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object"));
	Object->SetupAttachment(RootComponent);
	WC = CreateDefaultSubobject<UWidgetComponent>(TEXT("WC"));
	WC->SetupAttachment(Object);
	LAC = CreateDefaultSubobject<ULookAtComponent>(TEXT("LAC"));
}

void AAnomaly_Object_Neapolitan::BeginPlay()
{
	Super::BeginPlay();
	bSolved = false;
	if (!WC) return;
	UI_Interact = Cast<UUI_Interact>(WC->GetUserWidgetObject());
	UI_Interact->SetDescription(LOCTEXT("Key1", "상호작용"));
	LAC->SettingWidgetComponent(WC);
}

#pragma endregion

#undef LOCTEXT_NAMESPACE

#pragma region Interact

void AAnomaly_Object_Neapolitan::Interacted_Implementation()
{
	bSolved = !bSolved;
}

void AAnomaly_Object_Neapolitan::ShowInteractWidget_Implementation(bool bIsShow)
{
	UI_Interact->ShowDescription(bIsShow);
}

#pragma endregion