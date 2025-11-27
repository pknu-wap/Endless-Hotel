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
	
protected:
	UPROPERTY()
	TObjectPtr<class USceneComponent> Root;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> PlantMesh;

#pragma endregion

#pragma region

public:
	void ChangeToAfterState();

protected:
	UPROPERTY(VisibleAnywhere)
	bool bIsAfterState = false;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMesh> Mesh_After;

#pragma endregion
};
