// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include "Anomaly_Door.generated.h"

class UBoxComponent;
class AAnomaly_Object_Door;

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Door : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Door(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Activity

public:
	virtual void ActivateAnomaly() override;

#pragma endregion

#pragma region Door

protected:
	virtual void StartAnomalyAction() override;

protected:
	uint8 CurrentIndex = 1;
	const uint8 MaxIndex = 10;

	float NextActionDelay = 1.f;

#pragma endregion

#pragma region Door
protected:
	void SetupDoorTrigger();

	UFUNCTION()
	void OnTriggerBox_OpenBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OverlappedComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggerBox_CloseBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OverlappedComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Anomaly|Trigger")
	TObjectPtr<UBoxComponent> TriggerBox_Open;

	UPROPERTY(VisibleAnywhere, Category = "Anomaly|Trigger")
	TObjectPtr<UBoxComponent> TriggerBox_Close;

	UPROPERTY()
	TObjectPtr<AAnomaly_Object_Door> TriggerTargetDoor;
};