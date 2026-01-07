// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Float.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Float : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()

#pragma region Base

public:
    AAnomaly_Object_Float(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void BeginPlay() override;

#pragma endregion

#pragma region Interact

public:
    virtual void Interacted_Implementation() override;

#pragma endregion

#pragma region Floating

public:
    void StartFloating();
    void StopFloating();
    void RestoreToOrigin();
    void FloatAccelerate();

protected:
    FTimerHandle FloatTickTimer;
    FTimerHandle StopFloatTimer;

#pragma endregion

#pragma region Object

protected:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Mesh;

    FVector OriginLocation;
    FRotator OriginRotation;

    FVector FloatVelocity;
    FRotator RotationVelocity;

    bool bIsFloating = false;

#pragma endregion


};
