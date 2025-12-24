// Copyright by 2025-2 WAP Game 2 team

#include "Interact/IntertactTest.h"
#include "Components/StaticMeshComponent.h"

#define LOCTEXT_NAMESPACE "TestNameSpace"

// 실제 Interact 동작
void AInteractTest::Interacted_Implementation()
{
    RootComponent->AddLocalRotation(FRotator(0, 45, 0));

    UE_LOG(LogTemp, Warning, TEXT("InteractTest rotated 45 degrees"));
}

FText AInteractTest::GetDescriptionText_Implementation()
{
    return LOCTEXT("Key1", "TrashValue");
}

#undef LOCTEXT_NAMESPACE