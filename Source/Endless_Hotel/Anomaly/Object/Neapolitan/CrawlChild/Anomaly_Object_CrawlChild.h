// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_CrawlChild.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_CrawlChild : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class UAudioComponent> AC;

public:
	AAnomaly_Object_CrawlChild(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Trigger

protected:
	UPROPERTY(EditAnywhere, Category = "TriggerBox")
	TObjectPtr<class UBoxComponent> TriggerBox;

protected:
	UFUNCTION()
	void OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

#pragma endregion

#pragma region Collapse

protected:
	UPROPERTY(EditAnywhere, Category = "Collapse|Transform")
	FTransform StartTransform;

#pragma endregion

};
