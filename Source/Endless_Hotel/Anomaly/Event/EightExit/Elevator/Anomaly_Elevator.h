// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Event/EightExit/Anomaly_Event_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Elevator.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Elevator : public AAnomaly_Event_EightExit
{
	GENERATED_BODY()

#pragma region Elevator

protected:
	UPROPERTY(EditAnywhere, Category = "Movement|Elevator")
	TArray<FName> TargetAnomalyElevatorID;

	virtual void OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	TWeakObjectPtr<class AElevator> TargetElevator;

#pragma endregion

#pragma region ElevatorGhost

protected:
	UPROPERTY(EditAnyWhere, Category = "ElevatorGhost")
	TSubclassOf<class AElevatorGhost> ElevatorGhostClass;

	UPROPERTY(VisibleAnywhere, Category = "ElevatorGhost")
	TWeakObjectPtr<class AElevatorGhost> ElevatorGhost;

	UPROPERTY(EditAnywhere, Category = "ElevatorGhost")
	FTransform StartTransform;

#pragma endregion

#pragma region Activity

public:
	virtual void SetAnomalyState() override;

protected:
	virtual void StartAnomalyAction() override;
	virtual void DisableAnomaly() override;

#pragma endregion

};
