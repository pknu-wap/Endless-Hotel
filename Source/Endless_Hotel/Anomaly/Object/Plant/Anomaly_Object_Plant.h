// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Anomaly_Object_Plant.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Plant : public AAnomaly_Object_Base
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomaly_Object_Plant(const FObjectInitializer& ObjectInitializer);
	
#pragma endregion

#pragma region Change

	UPROPERTY(EditAnywhere, Category = "Plant");
	TObjectPtr<class UStaticMeshComponent> SM_Plant;

	UPROPERTY(EditAnywhere, Category = "Plant");
	TObjectPtr<class UStaticMeshComponent> SM_AfterPlant;

public:
	void StartChange();

#pragma endregion

#pragma region Plant Off
public:
		void StartPlantOff();
#pragma endregion
};
