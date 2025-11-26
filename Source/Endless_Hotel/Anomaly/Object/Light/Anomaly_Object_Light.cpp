// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Light/Anomaly_Object_Light.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/AudioComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
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
	Mesh_Destroy->SetNotifyBreaks(true);

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(RootComponent);

	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AC->SetupAttachment(RootComponent);
}

void AAnomaly_Object_Light::BeginPlay()
{
	Super::BeginPlay();

	Mesh_Destroy->OnChaosBreakEvent.RemoveDynamic(this, &ThisClass::LightDestroyed);
	Mesh_Destroy->OnChaosBreakEvent.AddDynamic(this, &ThisClass::LightDestroyed);
}

#pragma endregion

#pragma region Light

void AAnomaly_Object_Light::TurnOffLight()
{
	PointLight->bAffectsWorld = false;
	PointLight->MarkRenderStateDirty();
}

#pragma endregion

#pragma region Destroy

void AAnomaly_Object_Light::DropLight()
{
	Mesh_Default->SetSimulatePhysics(true);

	Mesh_Destroy->SetVisibility(true);
	Mesh_Destroy->SetSimulatePhysics(true);
	Mesh_Destroy->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	PointLight->AttachToComponent(Mesh_Default, FAttachmentTransformRules::KeepWorldTransform);
}

void AAnomaly_Object_Light::LightDestroyed(const FChaosBreakEvent& BreakEvent)
{
	Mesh_Default->SetVisibility(false);

	PointLight->bAffectsWorld = false;
	PointLight->MarkRenderStateDirty();

	AC->Sound = Sound_LightDestroy;
	AC->Play();
}

#pragma endregion

#pragma region Color

void AAnomaly_Object_Light::ChangeLightColor()
{
	PointLight->SetLightColor(FLinearColor(0, 0.9f, 1));
	PointLight->MarkRenderStateDirty();

	AC->Sound = Sound_LightBlue;
	AC->Play();
}

#pragma endregion