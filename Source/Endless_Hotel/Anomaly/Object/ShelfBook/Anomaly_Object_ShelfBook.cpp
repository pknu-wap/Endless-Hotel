// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/ShelfBook/Anomaly_Object_ShelfBook.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/AudioComponent.h"
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
	TriggerBox->SetGenerateOverlapEvents(true);
	TriggerBox->InitBoxExtent(FVector(100.f, 100.f, 100.f));
	TriggerBox->SetRelativeLocation(FVector(100.f, 0.f, 0.f));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AAnomaly_Object_ShelfBook::OnBooksFallRange);
	
	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AC->SetupAttachment(Root);
	AC->bAutoActivate = false;
}

void AAnomaly_Object_ShelfBook::BeginPlay()
{
	Super::BeginPlay();

	TArray<UStaticMeshComponent*> MeshComps;
	GetComponents<UStaticMeshComponent>(MeshComps);

	for (UStaticMeshComponent* Comp : MeshComps)
	{
		if (!Comp)
			continue;

		if (!Comp->ComponentHasTag(TEXT("Book")))
			continue;

		UStaticMeshComponent* BookMesh = Comp;
		BookComps.Add(BookMesh);

		BookMesh->SetNotifyRigidBodyCollision(true);
		BookMesh->OnComponentHit.AddDynamic(this, &ThisClass::OnBookHit);

		const FString ACName = FString::Printf(TEXT("AC_Book_%s"), *BookMesh->GetName());
		UAudioComponent* BookAC = NewObject<UAudioComponent>(this, *ACName);
		
		if (BookAC)
		{
			BookAC->bAutoActivate = false;
			BookAC->SetupAttachment(BookMesh);
			BookAC->RegisterComponent();

			BookAudioMap.Add(BookMesh, BookAC);
			BookLastSoundTimeMap.Add(BookMesh, -1000.0f);
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

void AAnomaly_Object_ShelfBook::OnBooksFallRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

	if (AC && Sound_BookDrop)
	{
		if (!AC->IsPlaying())
		{
			AC->SetSound(Sound_BookDrop);
			AC->Play();
		}
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
		Book->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Book->SetCollisionProfileName(TEXT("PhysicsActor"));
		Book->SetSimulatePhysics(true);
		Book->SetEnableGravity(true);
		Book->SetNotifyRigidBodyCollision(true);
		Book->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	}
}

#pragma endregion

#pragma region DropSound

void AAnomaly_Object_ShelfBook::OnBookHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (CurrentDropSoundCount >= MaxDropSoundCount)
	{
		return;
	}

	if (OtherComp && OtherComp->ComponentHasTag(TEXT("NoBookSound")))
	{
		return;
	}

	if (OtherComp && OtherComp->ComponentHasTag(TEXT("Book")))
	{
		return;
	}

	UStaticMeshComponent* BookMesh = Cast<UStaticMeshComponent>(HitComp);
	if (!BookMesh)
	{
		return;
	}
	if (!OtherComp)
	{
		return;
	}

	const float Now = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;

	float* LastTimePtr = BookLastSoundTimeMap.Find(BookMesh);
	if (LastTimePtr)
	{
		if ((Now - *LastTimePtr) < MinSoundInterval)
		{
			return;
		}
		*LastTimePtr = Now;
	}
	else
	{
		BookLastSoundTimeMap.Add(BookMesh, Now);
	}

	const FVector PlayLocation = Hit.ImpactPoint.IsNearlyZero() ? BookMesh->GetComponentLocation() : FVector(Hit.ImpactPoint);
	const float DropImpulse = NormalImpulse.Size();

	PlayRandomDropSound(BookMesh, PlayLocation, DropImpulse);

	CurrentDropSoundCount++;

}

void AAnomaly_Object_ShelfBook::PlayRandomDropSound(UStaticMeshComponent* BookMesh, const FVector& WorldLocation, float DropImpulse)
{
	if (!BookMesh)
	{
		return;
	}

	if (Sounds_BookDropRandom.Num() <= 0)
	{
		return;
	}

	UAudioComponent** ACPtr = BookAudioMap.Find(BookMesh);
	if (!ACPtr || !(*ACPtr))
	{
		return;
	}

	UAudioComponent* BookAC = *ACPtr;

	const int32 Index = FMath::RandRange(0, Sounds_BookDropRandom.Num() - 1);
	USoundWave* Pick = Sounds_BookDropRandom[Index];
	if (!Pick)
	{
		return;
	}

	BookAC->SetWorldLocation(WorldLocation);
	BookAC->SetSound(Pick);
	BookAC->Play();
}

#pragma endregion