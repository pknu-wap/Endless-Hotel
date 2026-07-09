// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/EightExit/Anomaly_Object_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Rug.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Rug : public AAnomaly_Object_EightExit
{
	GENERATED_BODY()
	
#pragma region Base

public:
	virtual void Reset() override;

#pragma endregion

#pragma region Color Change

public:
	void ChangeRugColor();

public:
	UPROPERTY(EditAnywhere, Category = "Material")
	TObjectPtr<class UMaterialInterface> ChangedMaterial;

	UPROPERTY(EditAnywhere, Category = "Material")
	TObjectPtr<class UMaterialInterface> OriginalMaterial;

#pragma endregion

};