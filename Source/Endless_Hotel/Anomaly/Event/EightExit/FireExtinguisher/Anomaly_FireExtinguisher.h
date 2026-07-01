// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Event/EightExit/Anomaly_Event_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_FireExtinguisher.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_FireExtinguisher : public AAnomaly_Event_EightExit
{
	GENERATED_BODY()

#pragma region Activity

public:
	virtual void SetAnomalyState() override;
	virtual void DisableAnomaly() override;

protected:
	virtual void StartAnomalyAction() override;

#pragma endregion

#pragma region Blur

protected:
	void ShowBlurWiget(bool bIsStart);

protected:
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> SW_Blur;

private:
	FTimerHandle FadeOutHandle;

	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC;

#pragma endregion

#pragma region Down

private:
	void PlayDownAnimMontage();

protected:
	UPROPERTY(EditAnywhere, Category = "Animation")
	TObjectPtr<UAnimMontage> AM_DownUp;

#pragma endregion

};