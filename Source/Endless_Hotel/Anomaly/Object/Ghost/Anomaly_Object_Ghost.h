// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraShakeBase.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Anomaly_Object_Ghost.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Ghost : public AAnomaly_Object_Base
{
    GENERATED_BODY()

#pragma region Base

public:
    AAnomaly_Object_Ghost(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

#pragma endregion

#pragma region Step
public:
    void StartGhostSequence();

private:
    void Reveal();
    void StartStep();
    void MoveStep();
    void FinishSequence();
    void FadeScreen(bool bFadeOut);
    void TurnOffLights();
    void TurnOnLights();
    void RevealWithLightDelay();
    void Hide();

private:
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* Mesh;

    UPROPERTY(EditAnywhere)
    float TriggerX = 5000.f;

    UPROPERTY(EditAnywhere, Category = "Ghost|Effects")
    TSubclassOf<UCameraShakeBase> CameraShakeClass;

    UPROPERTY()
    TObjectPtr<class UAudioComponent> AC;

    UPROPERTY(EditAnywhere)
    TObjectPtr<class USoundWave> Sound_On;

    UPROPERTY(EditAnywhere)
    TObjectPtr<class USoundWave> Sound_Off;

    UPROPERTY(EditAnywhere)
    TObjectPtr<class USoundWave> Sound_Shake;

    UPROPERTY(EditAnywhere)
    TObjectPtr<class USoundWave> Sound_Fin;

    ACharacter* Player;
    APlayerController* PC;

    FVector SpawnLocation;
    int32 StepIndex;

public:
    bool bTriggerEnabled = false;
    bool bAnomalyTriggered = false;
    bool bHasTriggered = false;
    bool bHasRevealedOnce = false;
};

#pragma endregion