// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Actor/Interact/Acquire/InteractAcquire.h"
#include "Type/Anomaly/Type_AnomalyRule.h"
#include "Type/Anomaly/Type_AnomalyID.h"
#include <CoreMinimal.h>
#include <ManualFragment.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AManualFragment : public AInteractAcquire
{
    GENERATED_BODY()

#pragma region Base

public:
    AManualFragment(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void BeginPlay() override;

#pragma endregion

#pragma region Acquire

protected:
    virtual void SaveAcquireData() override;

#pragma endregion

#pragma region Description

private:
    UPROPERTY(EditAnywhere)
    TObjectPtr<class UWidgetComponent> Comp_Description;

#pragma endregion

#pragma region Setting

private:
    UFUNCTION()
    void SetManualFragment();

private:
    UPROPERTY(EditAnywhere, Category = "Setting")
    EAnomalyRule NewRule;

    UPROPERTY(EditAnywhere, Category = "Setting")
    EAnomalyID AppearAnomaly;

    UPROPERTY(EditAnywhere, Category = "Setting")
    FText Description;

    UPROPERTY(EditAnywhere, Category = "Setting|Fake")
    bool bHasFakeRule = false;

    UPROPERTY(EditAnywhere, Category = "Setting|Fake", meta = (EditCondition = "bHasFakeRule"))
    EFakeRule FakeRule = EFakeRule::None;

#pragma endregion

};