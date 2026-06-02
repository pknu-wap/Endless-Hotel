// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/EightExit/Shelf/Anomaly_Object_Shelf.h"
#include <Components/StaticMeshComponent.h>
#include <Components/SceneComponent.h>

#pragma region Base

AAnomaly_Object_Shelf::AAnomaly_Object_Shelf(const FObjectInitializer& ObjectInitializer)
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

void AAnomaly_Object_Shelf::StartChange()
{
	SM_Plant->SetVisibility(false);
	SM_AfterPlant->SetVisibility(true);
}

#pragma endregion