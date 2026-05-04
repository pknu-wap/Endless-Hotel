// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/EightExit/Shelf/Anomaly_Object_Shelf.h"
#include <Components/StaticMeshComponent.h>
#include <Components/SceneComponent.h>
#include <Components/AudioComponent.h>

#pragma region Base

AAnomaly_Object_Shelf::AAnomaly_Object_Shelf(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SM_Plant = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Plant"));
	SM_Plant->SetupAttachment(RootComponent);

	SM_AfterPlant = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_AfterPlant"));
	SM_AfterPlant->SetupAttachment(RootComponent);
	SM_AfterPlant->SetVisibility(false);

	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AC->SetupAttachment(RootComponent);
	AC->bAutoActivate = false;
}

void AAnomaly_Object_Shelf::BeginPlay()
{
	Super::BeginPlay();

	TArray<UStaticMeshComponent*> MeshComps;
	GetComponents<UStaticMeshComponent>(MeshComps);

	for (UStaticMeshComponent* Comp : MeshComps)
	{
		if (!Comp->ComponentHasTag(TEXT("Book")))
		{
			continue;
		}
		BookComps.Add(Comp);
	}
}
#pragma endregion

#pragma region Change

void AAnomaly_Object_Shelf::StartChange()
{
	SM_Plant->SetVisibility(false);
	SM_AfterPlant->SetVisibility(true);
}

#pragma endregion

#pragma region Fall

void AAnomaly_Object_Shelf::FallSound()
{
	if (AC && Sound_BookDrop)
	{
		if (!AC->IsPlaying())
		{
			AC->SetSound(Sound_BookDrop);
			AC->Play();
		}
	}
	ShelfBooksFall();
}

void AAnomaly_Object_Shelf::ShelfBooksFall()
{
	for (auto& Book : BookComps)
	{
		if (!Book)
			continue;

		Book->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
		Book->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Book->SetCollisionProfileName(TEXT("PhysicsActor"));
		Book->SetSimulatePhysics(true);
		Book->SetEnableGravity(true);
		Book->SetNotifyRigidBodyCollision(true);
		Book->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	}
}

#pragma endregion