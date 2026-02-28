// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_SignDrop.generated.h>

class ARoomSignActor;

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_SignDrop : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()

#pragma region Drop

public:
	void ExecuteSignDrop();
	void AttachSignToMe(AActor* TargetActor);

protected:
	UPROPERTY(EditAnywhere, Category = "Anomaly|Sign")
	TArray<ARoomSignActor*> RoomSigns;

	UPROPERTY(EditAnywhere, Category = "Anomaly|Sign")
	TSubclassOf<UCameraShakeBase> CameraShakeClass;

protected:
	UFUNCTION()
	void OnSignRestored();

#pragma endregion 
};
