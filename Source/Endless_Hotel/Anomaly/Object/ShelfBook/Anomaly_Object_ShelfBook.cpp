// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/ShelfBook/Anomaly_Object_ShelfBook.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

#pragma region Base

AAnomaly_Object_ShelfBook::AAnomaly_Object_ShelfBook(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(Root);
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TriggerBox->InitBoxExtent(FVector(100.f, 100.f, 100.f));
	TriggerBox->SetRelativeLocation(FVector(100.f, 0.f, 0.f));

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AAnomaly_Object_ShelfBook::OnBooksFallRange);
}

void AAnomaly_Object_ShelfBook::BeginPlay()
{
	Super::BeginPlay();

	TArray<USceneComponent*> AllComps;
	GetComponents(UStaticMeshComponent:: StaticClass(), AllComps);

	for (UActorComponent* Comp : AllComps)
	{
		if (Comp && Comp->ComponentHasTag(TEXT("Book")))
		{
			if (UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(Comp))
			{
				BookComps.Add(Mesh);
			}
		}
	}
}

#pragma endregion

#pragma region Fall

void AAnomaly_Object_ShelfBook::ActiveTrigger()
{
	if (TriggerBox)
	{
		TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void AAnomaly_Object_ShelfBook::OnBooksFallRange(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (bIsFallen)
	{
		return;
	}
	bIsFallen = true;

	if (TriggerBox)
	{
		TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	BooksFall();
}

void AAnomaly_Object_ShelfBook::BooksFall()
{
	for (auto& Book : BookComps)
	{
		if (!Book)
			continue;

		Book->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
		Book->SetSimulatePhysics(true);
		Book->SetEnableGravity(true);

		if (Sound_BookDrop)
		{
			UGameplayStatics::PlaySoundAtLocation(this, Sound_BookDrop, Book->GetComponentLocation());
		}
	}
}

#pragma endregion
