// Copyright by 2025-2 WAP Game 2 team


#include "Actor/ChooseKey/ChooseKey.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"

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

    UAnomalyProgressSubSystem* APSS = Cast<UAnomalyProgressSubSystem>(GetGameInstance());
    if (APSS)
    {
        // 1. 이미 결정된 열쇠가 있는지 확인
        if (APSS->GlobalSelectedKeyIndex == 0)
        {
            // 게임 시작 후 처음 배치되는 경우에만 랜덤 결정
            APSS->GlobalSelectedKeyIndex = FMath::RandRange(1, 2);
        }

        // 2. 인스턴스에 저장된 정답을 가져와서 내 상태로 설정
        SelectedKeyIndex = APSS->GlobalSelectedKeyIndex;
    }

    // 3. 결정된 값에 따라 메쉬 설정 (기존 로직)
    bool bIsKey1 = (SelectedKeyIndex == 1);
    KeyMesh1->SetVisibility(bIsKey1);
    KeyMesh1->SetCollisionEnabled(bIsKey1 ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
    KeyMesh2->SetVisibility(!bIsKey1);
    KeyMesh2->SetCollisionEnabled(!bIsKey1 ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
}