// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Actor/EHActor.h"
#include "Interact/InteractableObject.h"
#include "IntertactTest.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AInteractTest : public AEHActor, public IInteractableObject
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* CubeMesh;

public:
    virtual void Interacted_Implementation() override;

    virtual FText GetDescriptionText_Implementation() override;
};