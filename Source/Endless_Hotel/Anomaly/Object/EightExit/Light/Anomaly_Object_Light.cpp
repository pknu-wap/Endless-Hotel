// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/EightExit/Light/Anomaly_Object_Light.h"
#include <Components/StaticMeshComponent.h>
#include <Components/PointLightComponent.h>
#include <Components/AudioComponent.h>
#include <GeometryCollection/GeometryCollectionComponent.h>
#include <Physics/Experimental/ChaosEventType.h>

#pragma region Base

AAnomaly_Object_Light::AAnomaly_Object_Light(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Mesh_Destroy = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("Mesh_Destroy"));
	Mesh_Destroy->SetupAttachment(RootComponent);
	SetGeometryCollection();
	
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(RootComponent);

	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AC->SetupAttachment(RootComponent);
}

void AAnomaly_Object_Light::BeginPlay()
{
	Super::BeginPlay();

	OriginalColor = PointLight->GetLightColor();

	Mesh_Destroy->OnChaosBreakEvent.AddUniqueDynamic(this, &ThisClass::LightDestroyed);
}

#pragma endregion

#pragma region Reset

void AAnomaly_Object_Light::Reset()
{
	Object->SetVisibility(true);

	Mesh_Destroy->DestroyComponent();
	Mesh_Destroy = NewObject<UGeometryCollectionComponent>(this);
	Mesh_Destroy->AttachToComponent(Object, FAttachmentTransformRules::KeepRelativeTransform);
	Mesh_Destroy->RegisterComponent();
	Mesh_Destroy->SetRestCollection(GC_Light);
	Mesh_Destroy->OnChaosBreakEvent.AddUniqueDynamic(this, &ThisClass::LightDestroyed);

	SetGeometryCollection();

	PointLight->SetLightColor(OriginalColor);
	PointLight->AttachToComponent(Object, FAttachmentTransformRules::KeepWorldTransform);

	TurnLight(true);

	Super::Reset();
}

#pragma endregion

#pragma region Light

void AAnomaly_Object_Light::TurnLight(bool bIsOn)
{
	PointLight->SetVisibility(bIsOn);
	PointLight->SetActive(bIsOn);
	PointLight->bAffectsWorld = bIsOn;
	PointLight->MarkRenderStateDirty();
}

#pragma endregion

#pragma region Destroy

void AAnomaly_Object_Light::SetGeometryCollection()
{
	Mesh_Destroy->SetVisibility(false);
	Mesh_Destroy->SetSimulatePhysics(false);
	Mesh_Destroy->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh_Destroy->SetNotifyBreaks(true);
}

void AAnomaly_Object_Light::StartDropLight()
{
	FTimerHandle DropHandle;
	GetWorld()->GetTimerManager().SetTimer(DropHandle, this, &ThisClass::DropLight, LightIndex * 0.5f, false);
}

void AAnomaly_Object_Light::DropLight()
{
	Object->SetVisibility(false);

	PointLight->AttachToComponent(Mesh_Destroy, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	Mesh_Destroy->SetVisibility(true);
	Mesh_Destroy->SetCollisionProfileName(TEXT("PhysicsActor"));
	Mesh_Destroy->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh_Destroy->SetEnableGravity(true);
	Mesh_Destroy->SetSimulatePhysics(true);
}

void AAnomaly_Object_Light::LightDestroyed(const FChaosBreakEvent& BreakEvent)
{
	Object->SetVisibility(false);
	Object->SetActive(false);

	TurnLight(false);

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