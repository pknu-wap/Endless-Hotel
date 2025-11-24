// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Interact/Interact_Base.h"
#include "IntertactTest.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AInteractTest : public AInteract_Base
{
    GENERATED_BODY()

public:
    AInteractTest();

protected:
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* CubeMesh;

public:
    virtual void Interact_Implementation(APlayerController* Controller) override;

};