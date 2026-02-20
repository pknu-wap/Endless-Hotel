// Copyright by 2025-2 WAP Game 2 team


#include "Actor/ChooseKey/ChooseKey.h"
#include "GameSystem/SubSystem/GameSystem.h"

AActor_Choose_Frame::AActor_Choose_Frame(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	KeyMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh1"));
	KeyMesh1->SetupAttachment(RootComponent);

	KeyMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh2"));
	KeyMesh2->SetupAttachment(RootComponent);
}

void AActor_Choose_Frame::BeginPlay()
{
    Super::BeginPlay();

    if (UGameInstance* GI = GetGameInstance())
    {
        UGameSystem* APSS = GI->GetSubsystem<UGameSystem>();

        if (APSS)
        {
            if (APSS->GlobalSelectedKeyIndex == 0)
            {
                APSS->GlobalSelectedKeyIndex = FMath::RandRange(1, 2);
            }

            SelectedKeyIndex = APSS->GlobalSelectedKeyIndex;
        }
    }
    bool bIsKey1 = (SelectedKeyIndex == 1);
    KeyMesh1->SetVisibility(bIsKey1);
    KeyMesh1->SetCollisionEnabled(bIsKey1 ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
    KeyMesh2->SetVisibility(!bIsKey1);
    KeyMesh2->SetCollisionEnabled(!bIsKey1 ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
}