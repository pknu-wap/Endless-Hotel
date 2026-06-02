// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/EightExit/Anomaly_Object_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Shelf.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Shelf : public AAnomaly_Object_EightExit
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_Shelf(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Change

	UPROPERTY(EditAnywhere, Category = "Plant");
	TObjectPtr<class UStaticMeshComponent> SM_Plant;

	UPROPERTY(EditAnywhere, Category = "Plant");
	TObjectPtr<class UStaticMeshComponent> SM_AfterPlant;

public:
	void StartChange();

#pragma endregion

};