// Copyright by 2025-2 WAP Game 2 team

#include "Actor/ChooseKey/ChooseKey.h"
#include "GameSystem/SubSystem/GameSystem.h"

#pragma region Base

AChooseKey::AChooseKey(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    Comp_Key = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
    SetRootComponent(Comp_Key);
}

void AChooseKey::BeginPlay()
{
    Super::BeginPlay();

    UGameSystem* GameSystem = GetGameInstance()->GetSubsystem<UGameSystem>();
    const uint8 Index = GameSystem->ChooseKeyIndex;
    UStaticMesh* TargetMesh = Index == 1 ? KeyMesh1 : KeyMesh2;

    if (Index == 2)
    {
        Comp_Key->SetRelativeScale3D(FVector(1, 1, 1));
    }

    Comp_Key->SetStaticMesh(TargetMesh);
}

#pragma endregion