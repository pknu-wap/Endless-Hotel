// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Plant/Anomaly_Object_Plant.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

#pragma region Base

AAnomaly_Object_Plant::AAnomaly_Object_Plant(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SM_Plant = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Plant"));
	SM_Plant->SetupAttachment(RootComponent);

	SM_AfterPlant = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_AfterPlant"));
	SM_AfterPlant->SetupAttachment(RootComponent);
	SM_AfterPlant->SetVisibility(false);
}

#pragma endregion

#pragma region Change

void AAnomaly_Object_Plant::StartChange()
{
	SM_Plant->SetVisibility(false);
	SM_AfterPlant->SetVisibility(true);
}

#pragma endregion

#pragma region Plant Off
void AAnomaly_Object_Plant::StartPlantOff()
{
	SetActorHiddenInGame(true);
}

