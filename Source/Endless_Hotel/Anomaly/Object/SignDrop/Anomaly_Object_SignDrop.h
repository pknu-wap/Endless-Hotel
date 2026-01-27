// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_SignDrop.generated.h>

class ARoomSignActor;

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_SignDrop : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomaly_Object_SignDrop(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Interact

public:
	virtual void SetInteraction() override;

#pragma endregion

#pragma region Drop

public:
	void ExecuteSignDrop();
	void AttachSignToMe(AActor* TargetActor);

protected:
	UPROPERTY(EditAnywhere, Category = "Anomaly|Sign")
	TArray<ARoomSignActor*> RoomSigns;

#pragma endregion 
};
