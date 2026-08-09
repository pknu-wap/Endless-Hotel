// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/EightExit/Anomaly_Object_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Light.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Light : public AAnomaly_Object_EightExit
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomaly_Object_Light(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Reset

public:
	virtual void Reset() override;

#pragma endregion

#pragma region Light

public:
	void TurnLight(bool bIsOn);

private:
	UPROPERTY(EditAnywhere, Category = "Index")
	int8 LightIndex = 0;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UPointLightComponent> PointLight;

	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC;

#pragma endregion

#pragma region Destroy

public:
	void StartDropLight();

private:
	void SetGeometryCollection();
	void DestroyLight();

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UGeometryCollectionComponent> Mesh_Destroy;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> Sound_LightDestroy;

	UPROPERTY(EditAnywhere, Category = "GeometryCollection")
	TObjectPtr<class UGeometryCollection> GC_Light;

#pragma endregion

#pragma region Color

public:
	void ChangeLightColor();

private:
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> Sound_LightBlue;

	UPROPERTY(EditAnywhere, Category = "Color")
	FLinearColor OriginalColor;

#pragma endregion

};