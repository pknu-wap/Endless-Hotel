// Copyright by 2025-2 WAP Game 2 team


#include "Interact/IntertactTest.h"
#include "Components/StaticMeshComponent.h"

// 기본 생성자
AInteractTest::AInteractTest(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = false;
}

// 실제 Interact 동작
void AInteractTest::Interacted()
{
    RootComponent->AddLocalRotation(FRotator(0, 45, 0));

    UE_LOG(LogTemp, Warning, TEXT("InteractTest rotated 45 degrees"));
}