// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/ShelfBook/Anomaly_Object_ShelfBook.h"
#include <Components/AudioComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/PrimitiveComponent.h>

#pragma region Base

AAnomaly_Object_ShelfBook::AAnomaly_Object_ShelfBook(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AC->SetupAttachment(RootComponent);
}

void AAnomaly_Object_ShelfBook::BeginPlay()
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

#pragma region Fall

void AAnomaly_Object_ShelfBook::FallSound()
{
	AC->SetSound(Sound_BookDrop);
	AC->Play();
	ShelfBooksFall();
}

void AAnomaly_Object_ShelfBook::ShelfBooksFall()
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