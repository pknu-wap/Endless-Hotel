// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Event/EightExit/Anomaly_Event_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_CryGhost.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_CryGhost : public AAnomaly_Event_EightExit
{
	GENERATED_BODY()
	
#pragma region Ghost

private:
	UPROPERTY()
	TObjectPtr<class ACryGhost> CryGhost;

#pragma endregion

#pragma region Activity

public:
	virtual void SetAnomalyState() override;
	virtual void DisableAnomaly() override;

#pragma endregion

#pragma region Trigger

protected:
	virtual void OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Ghost")
	TSubclassOf<class ACryGhost> GhostClass;

	UPROPERTY(EditAnywhere, Category = "Trigger")
	FTransform GhostSpawnTrans;

	UPROPERTY(EditAnywhere, Category = "Trigger")
	FTransform StandTrans;

	UPROPERTY(EditAnywhere, Category = "Trigger")
	FTransform JumpScareTrans;

#pragma endregion

};