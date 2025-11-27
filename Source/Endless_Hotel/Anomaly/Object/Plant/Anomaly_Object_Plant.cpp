// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Plant/Anomaly_Object_Plant.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

#pragma region Base

AAnomaly_Object_Plant::AAnomaly_Object_Plant(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	PlantMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlantMesh"));
	PlantMesh->SetupAttachment(RootComponent);
}

void AAnomaly_Object_Plant::ChangeToAfterState()
{
	if (bIsAfterState) return;
	bIsAfterState = true;

	if (PlantMesh && Mesh_After)
	{
		PlantMesh->SetStaticMesh(Mesh_After);
	}
}

#pragma endregion

