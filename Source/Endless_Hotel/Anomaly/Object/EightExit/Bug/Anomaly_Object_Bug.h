// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/EightExit/Anomaly_Object_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Bug.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Bug : public AAnomaly_Object_EightExit
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomaly_Object_Bug(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Bug

public:
	void ActiveBug();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UNiagaraComponent> NiagaraComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> AudioComponent;

#pragma endregion

};