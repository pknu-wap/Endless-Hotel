// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/EightExit/Anomaly_Object_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Ceiling.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Ceiling : public AAnomaly_Object_EightExit
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_Ceiling(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void Reset() override;

protected:
	UPROPERTY()
	TObjectPtr<class UTimelineComponent> Timeline;

	UPROPERTY(EditAnywhere, Category = "Time")
	TObjectPtr<UCurveFloat> Curve_CeilingRotate;

#pragma endregion

#pragma region Ceiling Rotate

public:
	UFUNCTION()
	void PlayCeilingRotate();

protected:
	UFUNCTION()
	void CeilingRotate(float Value);

#pragma endregion

#pragma region Ceiling Blood

public:
	void CeilingBloodDripping();

protected:
	UPROPERTY(EditAnywhere, Category = "Blood")
	TObjectPtr<class UNiagaraComponent> Niagara_Ceiling_Blood;

	UPROPERTY(EditAnywhere, Category = "Blood")
	FVector BloodLocationMin1;

	UPROPERTY(EditAnywhere, Category = "Blood")
	FVector BloodLocationMax1;

	UPROPERTY(EditAnywhere, Category = "Blood")
	FVector BloodLocationMin2;

	UPROPERTY(EditAnywhere, Category = "Blood")
	FVector BloodLocationMax2;

	UPROPERTY(EditAnywhere, Category = "Blood")
	float BloodInterval = 1;

	FTimerHandle BloodHandle;

#pragma endregion

#pragma region Collapsing

public:
	void TriggerCeilingCollapse();
	void SetupCrawlChildCeilingObject();

public:
	UPROPERTY(EditAnywhere, Category = "Destruction")
	TObjectPtr<class UGeometryCollectionComponent> GeometryCollection_Ceiling;

	UPROPERTY(EditAnywhere, Category = "Ceiling|Collapse")
	TSubclassOf<class AFieldSystemActor> FieldSystemActorClass;

	UPROPERTY()
	TWeakObjectPtr<class AFieldSystemActor> ActiveCollapseFieldWeak;

	UPROPERTY(EditAnywhere, Category = "Destruction")
	TObjectPtr<class UBoxComponent> CollapseRegionBox;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	TWeakObjectPtr<class ACrawlChild> CrawlChild;

protected:
	bool bHasCollapsed = false;

#pragma endregion

};