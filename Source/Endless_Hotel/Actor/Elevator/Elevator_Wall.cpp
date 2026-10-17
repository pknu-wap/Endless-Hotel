// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Elevator/Elevator_Wall.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include <Kismet/KismetSystemLibrary.h>

#pragma region Base

AElevator_Wall::AElevator_Wall(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    Wall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall"));
    RootComponent = Wall;
}

void AElevator_Wall::ResetWall()
{
    const auto* GI = GetGameInstance();
    auto* VerdictSys = GI->GetSubsystem<UAnomalyVerdictSubsystem>();
    auto* GameSys = GI->GetSubsystem<UGameSystem>();
    if (GameSys->GetGameProgression() == EGameProgression::CheckIn && bIsCinematic)
    {
        SetActorLocation(StandardLocation + CinematicLocation);
        return;
    }
    FVector StartLocation = VerdictSys->bIsStartInBed && bIsOver ? StandardLocation + End : StandardLocation + Start;
    FLatentActionInfo LatentInfo;
    LatentInfo.CallbackTarget = this;
    LatentInfo.UUID = 1000;
    LatentInfo.Linkage = 0;

    UKismetSystemLibrary::MoveComponentTo(RootComponent, StandardLocation + End, RootComponent->GetRelativeRotation(), false, false, 0.0f, false, EMoveComponentAction::Stop, LatentInfo);
    SetActorLocation(StartLocation);
}

#pragma endregion

#pragma region Move

void AElevator_Wall::MoveWall(float MoveDuration)
{
    FLatentActionInfo LatentInfo;
    LatentInfo.CallbackTarget = this;
    LatentInfo.UUID = 1000;
    LatentInfo.Linkage = 0;

    UKismetSystemLibrary::MoveComponentTo(RootComponent, StandardLocation + End, RootComponent->GetRelativeRotation(), false, false, MoveDuration, false, EMoveComponentAction::Move, LatentInfo);
}

#pragma endregion