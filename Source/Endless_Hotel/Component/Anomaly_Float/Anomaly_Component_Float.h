// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Component/EHComponent.h"
#include "Anomaly/Object/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Component_Float.generated.h>

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ENDLESS_HOTEL_API UAnomaly_Component_Float : public UEHComponent
{
	GENERATED_BODY()
	
#pragma region Base

public:
    UAnomaly_Component_Float(const FObjectInitializer& ObjectInitializer);

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

private:
    void FloatTick();

    UPROPERTY()
    UPrimitiveComponent* TargetMesh;

    FTimerHandle FloatTickTimer;
    FTimerHandle StopFloatTimer;

    FVector FloatVelocity;
    FRotator RotationVelocity;
    bool bIsFloating;

    float TickInterval = 0.016f;

#pragma endregion

};

