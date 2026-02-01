// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Anomaly_Object_Base.h"
#include <CoreMinimal.h>
#include <Anomlay_Object_Rug.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomlay_Object_Rug : public AAnomaly_Object_Base
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomlay_Object_Rug(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UMaterialInterface> ChangedMaterial;

#pragma endregion

#pragma region Color Change

public:
	void ChangeRugColor();

#pragma endregion

};
