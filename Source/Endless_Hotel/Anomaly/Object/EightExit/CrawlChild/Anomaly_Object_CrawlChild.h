// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Anomaly/Object/EightExit/Anomaly_Object_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_CrawlChild.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_CrawlChild : public AAnomaly_Object_EightExit
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class UAudioComponent> ObjectAC;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class UAudioComponent> ChildAC;

public:
	AAnomaly_Object_CrawlChild(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region ReadyAnomaly

public:
	void SetupCrawlChildObject();

#pragma endregion

#pragma region Trigger

protected:
	UPROPERTY(EditAnywhere, Category = "TriggerBox")
	TObjectPtr<class UBoxComponent> TriggerBox;

	UPROPERTY(EditAnywhere, Category = "TriggerBox")
	FTransform TriggerBox_Transform;

public:
	void ActiveTriggerBox();

protected:
	UFUNCTION()
	void OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

#pragma endregion

#pragma region Collapse

protected:
	UPROPERTY(EditAnywhere, Category = "Collapse|Transform")
	FTransform StartTransform;

	UPROPERTY(EditAnywhere, Category = "Collapse|Transform")
	FTransform EndTransform;

	TObjectPtr<class UTimelineComponent> FallTimeline;

	UPROPERTY(EditAnywhere, Category = "Collapse|Curve")
	TObjectPtr<UCurveFloat> FallCurve;

private:
	UFUNCTION()
	void OnFallTimelineUpdate(float Alpha);

	UFUNCTION()
	void OnFallTimelineFinished();

#pragma endregion

#pragma region AI

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	FTransform AIEndTransform;

	TWeakObjectPtr<class ACrawlChild> CrawlChild;

public:
	UFUNCTION()
	void OnCrawlChildSpawnedHandler(ACrawlChild* SpawnedCrawlChild);

#pragma endregion

};
