// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include "Anomaly_ShelfBook.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_ShelfBook : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()

#pragma region Activitiy

public:
	virtual void ActivateAnomaly(uint8 Anomaly_ID) override;

#pragma endregion
};
