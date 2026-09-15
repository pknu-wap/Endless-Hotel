// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_SignDrop.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_SignDrop : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()

#pragma region Reset

public:
	virtual void Reset() override;

#pragma endregion

#pragma region Drop

public:
	void ExecuteSignDrop();

private:
	void DropSign();

private:
	UPROPERTY(EditAnywhere, Category = "Sign")
	TArray<TWeakObjectPtr<class ARoomSignActor>> RoomSigns;

	UPROPERTY(EditAnywhere, Category = "Sign")
	TSubclassOf<UCameraShakeBase> CameraShakeClass;

	UPROPERTY(EditAnywhere, Category = "Sign")
	TObjectPtr<USoundBase> DropSound;

	UPROPERTY()
	TWeakObjectPtr<class ARoomSignActor> TargetSign;

#pragma endregion 

#pragma region Interact

public:
	virtual void Interact(class AEHCharacter* Interacter) override;

#pragma endregion

};