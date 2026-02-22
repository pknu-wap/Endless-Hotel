// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Event_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Door.generated.h>

class UBoxComponent;
class AAnomaly_Object_Door;

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Door : public AAnomaly_Event_EightExit
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Door(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Activity

public:
	virtual void SetAnomalyActivate() override;

#pragma endregion

#pragma region Trigger

protected:
	void SetupDoorTrigger();

#pragma endregion

#pragma region Door
	
protected:
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

#pragma endregion

};