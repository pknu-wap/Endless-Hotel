// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/EightExit/Anomaly_Object_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Fire.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Fire : public AAnomaly_Object_EightExit
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomaly_Object_Fire(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Fire

private:
	void StartFire();

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UNiagaraComponent> NiagaraComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> AudioComponent;

	UPROPERTY(EditAnywhere, Category = "Fire")
	TObjectPtr<class USoundWave> SW_First;

	static bool bIsFirst;

#pragma endregion

#pragma region Death

private:
	UFUNCTION()
	void OnDeathRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> DeathTrigger;

#pragma endregion

};