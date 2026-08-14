// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/EightExit/ShelfPlant/Anomaly_Object_ShelfPlant.h"
#include <Components/StaticMeshComponent.h>
#include <Components/SceneComponent.h>

#pragma region Base

AAnomaly_Object_ShelfPlant::AAnomaly_Object_ShelfPlant(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SM_Plant = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Plant"));
	SM_Plant->SetupAttachment(RootComponent);

	SM_AfterPlant = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_AfterPlant"));
	SM_AfterPlant->SetupAttachment(RootComponent);
	SM_AfterPlant->SetVisibility(false);
}

#pragma endregion

#pragma region Reset

void AAnomaly_Object_ShelfPlant::Reset()
{
	Super::Reset();

	SM_Plant->SetVisibility(true);
	SM_AfterPlant->SetVisibility(false);
}

#pragma endregion

#pragma region Change

void AAnomaly_Object_ShelfPlant::StartChange()
{
	SM_Plant->SetVisibility(false);
	SM_AfterPlant->SetVisibility(true);
}

#pragma endregion