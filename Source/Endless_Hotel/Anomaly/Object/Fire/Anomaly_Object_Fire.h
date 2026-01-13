// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Anomaly_Object_Base.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Fire.generated.h>

#pragma region Declare

class UNiagaraSystem;

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Fire : public AAnomaly_Object_Base
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomaly_Object_Fire(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Fire

public:
	void StartFire(UNiagaraSystem* Effect);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UNiagaraComponent> NiagaraComponent;

	UPROPERTY()
	TObjectPtr<class UNiagaraSystem> NS_FireEffect;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> AudioComponent;

	UPROPERTY(EditAnywhere, Category = "Fire")
	TObjectPtr<class USoundWave> SW_First;

	static bool bIsFirst;

#pragma endregion

#pragma region Death

protected:
	UFUNCTION()
	void OnDeathRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> DeathTrigger;

#pragma endregion

};