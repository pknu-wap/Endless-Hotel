// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Component/EHComponent.h"
#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <FloatComponent.generated.h>

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ENDLESS_HOTEL_API UFloatComponent : public UEHComponent
{
    GENERATED_BODY()

#pragma region Base

public:
    UFloatComponent(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void BeginPlay() override;

#pragma endregion

#pragma region Interact


#pragma endregion

#pragma region Float

public:
    UFUNCTION(BlueprintCallable, Category = "Anomaly")
    void StartFloating();

    UFUNCTION(BlueprintCallable, Category = "Anomaly")
    void StopFloating();

    bool bIsFloating;
    bool bIsFloatStarted;

private:
    void FloatTick();
    void FreezePhysics();

    UPROPERTY()
    TObjectPtr<class UPrimitiveComponent> TargetMesh;

    FTimerHandle FloatTickTimer;
    FTimerHandle StopFloatTimer;
    FTimerHandle FreezeTimerHandle;

    FVector FloatVelocity;
    FRotator RotationVelocity;


    float TickInterval = 0.016f;

#pragma endregion
};

