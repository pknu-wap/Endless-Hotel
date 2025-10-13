// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Light/Anomaly_Object_Light.h"
#include "Components/StaticMeshComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Components/PointLightComponent.h"
#include "Physics/Experimental/ChaosEventType.h"

#pragma region Base

AAnomaly_Object_Light::AAnomaly_Object_Light(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Mesh_Default = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Default"));
	SetRootComponent(Mesh_Default);

	Mesh_Destroy = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("Mesh_Destroy"));
	Mesh_Destroy->SetupAttachment(RootComponent);
	Mesh_Destroy->SetVisibility(false);
	Mesh_Destroy->SetSimulatePhysics(false);
	Mesh_Destroy->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh_Destroy->OnChaosBreakEvent.AddDynamic(this, &ThisClass::LightDestroyed);

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(RootComponent);
}

#pragma endregion

#pragma region Destroy

void AAnomaly_Object_Light::DropLight()
{
	Mesh_Default->SetVisibility(false);
	Mesh_Default->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Mesh_Destroy->SetVisibility(true);
	Mesh_Destroy->SetSimulatePhysics(true);
	Mesh_Destroy->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	FVector Accel = FVector(0, 0, -300.0f);
	Mesh_Destroy->AddImpulse(Accel * Mesh_Destroy->GetMass());
}

void AAnomaly_Object_Light::LightDestroyed(const FChaosBreakEvent& BreakEvent)
{
	// 여기에 사운드 추가 예정
}

#pragma endregion