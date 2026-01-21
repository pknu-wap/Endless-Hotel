// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Anomaly_Object_Base.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Disappear.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Disappear : public AAnomaly_Object_Base
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomaly_Object_Disappear(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere, Category = "Disappear")
	TObjectPtr<class UStaticMeshComponent> SM_Object;

	UPROPERTY(EditAnywhere, Category = "Disappear")
	bool bVisible = true;

#pragma endregion

#pragma region Activity

public:
	void StartDisappear();
#pragma endregion
};
