// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interact_Base.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AInteract_Base : public AActor
{
    GENERATED_BODY()

public:
    AInteract_Base(const FObjectInitializer& ObjectInitializer);

    //상호작용 함수 선언
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
    void Interact(APlayerController* InteractingController);
};