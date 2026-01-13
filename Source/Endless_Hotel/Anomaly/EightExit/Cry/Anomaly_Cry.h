// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include "Anomaly_Cry.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Cry : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomaly_Cry(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Activity

public:
	virtual void ActivateAnomaly() override;

#pragma endregion

#pragma region Cry

protected:
	UFUNCTION()
	void PlayCrySound();

protected:
	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> Sound_Cry;

#pragma endregion

};