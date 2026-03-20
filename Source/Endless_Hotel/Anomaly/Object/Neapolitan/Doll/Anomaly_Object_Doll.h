// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Doll.generated.h>

class UStaticMeshComponent;
class AActor;

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Doll : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_Doll(const FObjectInitializer& ObjectInitializer);
	
#pragma endregion

#pragma region Doll

public:
	void ActivateDoll_Show();

#pragma endregion

#pragma region Interact

public:
	virtual void Interact_Implementation(AEHCharacter* Interacter) override;

protected:
	void InteractFire();

	UFUNCTION()
	void InteractedMoveStep(int32 step);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UNiagaraComponent> Niagara_Fire;

#pragma endregion

};