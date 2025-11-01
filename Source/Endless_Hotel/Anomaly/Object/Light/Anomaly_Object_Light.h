// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Anomaly_Object_Light.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Light : public AAnomaly_Object_Base
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomaly_Object_Light(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	int32 LightIndex = 0;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh_Default;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UGeometryCollectionComponent> Mesh_Destroy;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UPointLightComponent> PointLight;

	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC;

#pragma endregion

#pragma region Destroy

public:
	void DropLight();

protected:
	UFUNCTION()
	void LightDestroyed(const struct FChaosBreakEvent& BreakEvent);

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> Sound_LightDestroy;

#pragma endregion

#pragma region Color

public:
	void ChangeLightColor();

protected:
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> Sound_LightBlue;

#pragma endregion

};