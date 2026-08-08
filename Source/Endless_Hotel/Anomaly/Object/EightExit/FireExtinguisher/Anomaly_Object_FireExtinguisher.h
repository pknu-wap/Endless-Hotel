// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Anomaly/Object/EightExit/Anomaly_Object_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_FireExtinguisher.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_FireExtinguisher : public AAnomaly_Object_EightExit
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomaly_Object_FireExtinguisher(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Reset

public:
	virtual void Reset() override;

#pragma endregion

#pragma region Explode

public:
	void Explode();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> AudioComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UNiagaraComponent> NiagaraComponent;

#pragma endregion

};