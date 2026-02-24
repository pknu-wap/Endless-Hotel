// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Event_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Cry.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Cry : public AAnomaly_Event_EightExit
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomaly_Cry(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Activity

public:
	virtual void SetAnomalyActivate() override;

protected:
	virtual void StartAnomalyAction() override;

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

	UPROPERTY(EditAnywhere, Category = "Sound")
	FVector CryLocation;

#pragma endregion

};