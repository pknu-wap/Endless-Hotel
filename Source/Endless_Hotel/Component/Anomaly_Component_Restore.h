// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Component/EHComponent.h"
#include <CoreMinimal.h>
#include <Anomaly_Component_Restore.generated.h>

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ENDLESS_HOTEL_API UAnomaly_Component_Restore : public UEHComponent
{
    GENERATED_BODY()

#pragma region Base

public:
    UAnomaly_Component_Restore(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void BeginPlay() override;

#pragma endregion 

#pragma region Restore

public:

    void SaveOriginalTransform();

    void StartRestoring(float Duration = 2.5f);

private:
    void RestoreTick();

    FTransform OriginalTransform;
    FTransform StartTransform;
    FTimerHandle RestoreHandle;

    float RestoreDuration = 2.5f;
    float RestoreCurrentTime = 0.f;

#pragma endregion

};