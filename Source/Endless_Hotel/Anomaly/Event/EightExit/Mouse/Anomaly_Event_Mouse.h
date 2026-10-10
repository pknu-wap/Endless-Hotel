// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Anomaly/Event/EightExit/Anomaly_Event_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Event_Mouse.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Event_Mouse : public AAnomaly_Event_EightExit
{
	GENERATED_BODY()
	
#pragma region Activity

public:
	virtual void SetAnomalyState() override;
	virtual void DisableAnomaly() override;

#pragma endregion

#pragma region Trigger

protected:
	virtual void OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Trigger")
	FTransform JumpScareTrans;

	bool bSpawnedMouse = false;

#pragma endregion

#pragma region Mouse

private:
	void SpawnMouse();
	void RunMouse();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Mouse")
	FTransform SpawnMouseTrans;

	UPROPERTY(EditDefaultsOnly, Category = "Mouse")
	TSubclassOf<class AMouse> MouseClass;

	UPROPERTY()
	TObjectPtr<class AMouse> SpawnedMouse;

#pragma endregion

#pragma region DeadBody

private:
	void SpawnDeadBody();
	void JumpScareDeadBody();

private:
	UPROPERTY(EditDefaultsOnly, Category = "DeadBody")
	FTransform SpawnDeadBodyTrans;

	UPROPERTY(EditDefaultsOnly, Category = "DeadBody")
	TObjectPtr<UAnimMontage> AM_JumpScare;

	UPROPERTY(EditDefaultsOnly, Category = "DeadBody")
	TSubclassOf<class ASkeletalMeshActor> DeadBodyClass;

	UPROPERTY()
	TObjectPtr<class ASkeletalMeshActor> SpawnedDeadBody;

#pragma endregion

};