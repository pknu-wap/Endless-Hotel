// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Anomaly_Object_Base.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Neapolitan.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Neapolitan : public AAnomaly_Object_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Verdict

public:
	bool bSolved = true;

#pragma endregion
};