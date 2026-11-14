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
    void StopPillSpawn();
    void ReleaseChild();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collapse")
    TObjectPtr<class UNiagaraComponent> PillNiagara;

    UPROPERTY(EditAnywhere, Category = "Collapse|Spawn", meta = (MakeEditWidget = true))
    FVector SpawnCenter = FVector(0.f, 0.f, 320.f);

    UPROPERTY(EditAnywhere, Category = "Collapse|Path", meta = (MakeEditWidget = true))
    FVector WallPoint = FVector(500.f, 0.f, 0.f);

    UPROPERTY(EditAnywhere, Category = "Collapse|Path", meta = (MakeEditWidget = true))
    FVector CornerPoint = FVector(500.f, 800.f, 0.f);

    UPROPERTY(EditAnywhere, Category = "Collapse|Path", meta = (MakeEditWidget = true))
    FVector HallEndPoint = FVector(500.f, 2500.f, 0.f);

    UPROPERTY(EditAnywhere, Category = "Collapse|Spawn", meta = (ClampMin = "1"))
    int32 PillCount = 3000;

    UPROPERTY(EditAnywhere, Category = "Collapse|Timing", meta = (ClampMin = "0.1"))
    float PillSpawnDuration = 8.f;

    UPROPERTY(EditAnywhere, Category = "Collapse|Timing", meta = (ClampMin = "0.01"))
    float ChildReleaseDelay = 0.8f;

private:
    FTimerHandle PillSpawnTimer;
    FTimerHandle ChildReleaseTimer;

#pragma endregion

#pragma region AI

protected:
    UPROPERTY(EditAnywhere, Category = "AI")
    FTransform AIEndTransform;

    UPROPERTY(VisibleAnywhere, Category = "AI")
    TWeakObjectPtr<class ACrawlChild> CrawlChild;

#pragma endregion
    
};