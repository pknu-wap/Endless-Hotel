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
	
private:
	void SpawnCryGhost(FTransform Trans);

protected:
	UPROPERTY(EditAnywhere, Category = "Ghost")
	TSubclassOf<class ACryGhost> GhostClass;

#pragma endregion

#pragma region Cry

private:
	void AdvanceCryGhostState();

protected:
	UPROPERTY(EditAnywhere, Category = "Cry")
	FTransform CrySpawnTrans;

	UPROPERTY(EditAnywhere, Category = "Cry")
	FTransform StandTrans;

	UPROPERTY(EditAnywhere, Category = "Cry")
	FTransform JumpScareTrans;

	UPROPERTY(EditAnywhere, Category = "Cry")
	FTransform CryTriggerTrans;

#pragma endregion

#pragma region Light

private:
	void TurnAllLights(bool bOn);
	void MakeNoiseSound();
	void PlayNoiseSound();

protected:
	UPROPERTY(EditAnywhere, Category = "Light")
	FTransform LightSpawnTrans;

	UPROPERTY(EditAnywhere, Category = "Light")
	FTransform LightTriggerTrans;

	UPROPERTY(EditAnywhere, Category = "Light")
	TObjectPtr<class USoundCue> SC_Noise;

private:
	FTimerHandle LightHandle;

	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC_Light;

#pragma endregion

};