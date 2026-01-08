// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Base_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_MusicBox.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_MusicBox : public AAnomaly_Base_Neapolitan
{
	GENERATED_BODY()
	
#pragma region Activity

public:
	virtual void ActivateAnomaly(uint8 Anomaly_ID) override;

#pragma endregion

};
