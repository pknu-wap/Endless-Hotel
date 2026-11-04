// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Anomaly/Object/EightExit/Anomaly_Object_EightExit.h"
#include <CoreMinimal.h>
#include <Engine/TimerHandle.h>
#include "Anomaly_Object_CrawlChild.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_CrawlChild : public AAnomaly_Object_EightExit
{
    GENERATED_BODY()

#pragma region Base

public:
    AAnomaly_Object_CrawlChild(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditAnywhere, Category = "Sound")
    TObjectPtr<class UAudioComponent> ObjectAC;

    UPROPERTY(EditAnywhere, Category = "Sound")
    TObjectPtr<class UAudioComponent> ChildAC;

    UPROPERTY(EditAnywhere, Category = "Transform")
    FTransform StartTransform;

#pragma endregion

#pragma region ReadyAnomaly

public:
    void SetupCrawlChildObject();
    void OnCrawlChildSpawnedHandler(class ACrawlChild* SpawnedCrawlChild);

#pragma endregion

#pragma region Trigger

public:
    void ActiveTriggerBox();

protected:
    UFUNCTION()
    void OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
    UPROPERTY(EditAnywhere, Category = "TriggerBox")
    TObjectPtr<class UBoxComponent> TriggerBox;

#pragma endregion

#pragma region Collapse

private:
    void StartPillCollapse();
    void SpawnPillBatch();
    void ClearPhysicsPills();
    void ReleaseChild();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collapse")
    TObjectPtr<class UInstancedStaticMeshComponent> PillISM;

    UPROPERTY(EditAnywhere, Category = "Collapse|Spawn")
    FVector SpawnCenter = FVector(0.f, 0.f, 320.f);

    UPROPERTY(EditAnywhere, Category = "Collapse|Spawn", meta = (ClampMin = "1"))
    int32 PillsPerBatch = 4;

    UPROPERTY(EditAnywhere, Category = "Collapse|Spawn", meta = (ClampMin = "1.0"))
    float SpawnSpacing = 40.f;

    UPROPERTY(EditAnywhere, Category = "Collapse|Timing", meta = (ClampMin = "0.01"))
    float BatchInterval = 0.3f;

    UPROPERTY(EditAnywhere, Category = "Collapse|Timing", meta = (ClampMin = "0.01"))
    float ChildReleaseDelay = 0.8f;

private:
    UPROPERTY(Transient)
    TArray<TObjectPtr<class UStaticMeshComponent>> PhysicsPills;

    TArray<FVector> PillScales;
    FTimerHandle PillSpawnTimer;
    FTimerHandle ChildReleaseTimer;

#pragma endregion

#pragma region Physics

protected:
    UPROPERTY(EditAnywhere, Category = "Collapse|Physics", meta = (ClampMin = "0.01"))
    float PillMassKg = 1.f;

    UPROPERTY(EditAnywhere, Category = "Collapse|Physics", meta = (ClampMin = "0.0"))
    float PillLinearDamping = 0.1f;

    UPROPERTY(EditAnywhere, Category = "Collapse|Physics", meta = (ClampMin = "0.0"))
    float PillAngularDamping = 3.f;

#pragma endregion

#pragma region AI

protected:
    UPROPERTY(EditAnywhere, Category = "AI")
    FTransform AIEndTransform;

    UPROPERTY(VisibleAnywhere, Category = "AI")
    TWeakObjectPtr<class ACrawlChild> CrawlChild;

#pragma endregion
    
};