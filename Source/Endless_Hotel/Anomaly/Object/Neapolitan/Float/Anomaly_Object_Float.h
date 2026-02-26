// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Float.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Float : public AAnomaly_Object_Neapolitan
{
    GENERATED_BODY()

#pragma region Base

protected:
    virtual void BeginPlay() override;

#pragma endregion

#pragma region Interact

private:
    UPROPERTY()
    TArray<AActor*> AffectedActors;

    TSet<AActor*> RestoredActors;

    void CheckAllRestored();

#pragma endregion

#pragma region Floating

public:
    void SearchAndStart();

    UFUNCTION()
    void OnActorRestored(AActor* RestoredActor);

#pragma endregion

    


};
