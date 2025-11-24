// Copyright by 2025-2 WAP Game 2 team


#include "Interact/IntertactTest.h"
#include "Components/StaticMeshComponent.h"

// 기본 생성자
AInteractTest::AInteractTest()
{
    PrimaryActorTick.bCanEverTick = true;

}

// 실제 Interact 동작
void AInteractTest::Interact_Implementation(APlayerController* Controller)
{
    RootComponent->AddLocalRotation(FRotator(0, 45, 0));

    UE_LOG(LogTemp, Warning, TEXT("InteractTest rotated 45 degrees"));
}