// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Twin.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Twin : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_Twin(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Twin

public:
	void StartTwin();

protected:
	UFUNCTION()
	virtual void OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	FTransform TwinTransform;

	UPROPERTY(EditAnywhere, Category = "Trigger")
	TObjectPtr<class UBoxComponent> TriggerBox;

#pragma endregion

};