// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Elevator/Elevator_Wall.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include <Kismet/KismetSystemLibrary.h>

#pragma region Base

AElevator_Wall::AElevator_Wall(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    Wall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall"));
    RootComponent = Wall;
}

void AElevator_Wall::BeginPlay()
{
    Super::BeginPlay();
    auto* Subsystem = GetGameInstance()->GetSubsystem<UGameSystem>();
    Subsystem->OnAnomalySpawned.AddDynamic(this, &ThisClass::ResetWall);
}

void AElevator_Wall::ResetWall()
{
    FLatentActionInfo LatentInfo;
    LatentInfo.CallbackTarget = this;
    LatentInfo.UUID = 1000;
    LatentInfo.Linkage = 0;

    UKismetSystemLibrary::MoveComponentTo(RootComponent, End, RootComponent->GetRelativeRotation(), false, false, 0.0f, false, EMoveComponentAction::Stop, LatentInfo);
    SetActorLocation(Start);
}

#pragma endregion

#pragma region Move

void AElevator_Wall::MoveWall(float MoveDuration)
{
    FLatentActionInfo LatentInfo;
    LatentInfo.CallbackTarget = this;
    LatentInfo.UUID = 1000;
    LatentInfo.Linkage = 0;

    UKismetSystemLibrary::MoveComponentTo(RootComponent, End, RootComponent->GetRelativeRotation(), false, false, MoveDuration, false, EMoveComponentAction::Move, LatentInfo);
}

#pragma endregion