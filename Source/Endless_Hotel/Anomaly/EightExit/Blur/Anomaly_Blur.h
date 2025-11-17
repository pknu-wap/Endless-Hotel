// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include "Anomaly_Blur.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Blur : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Blur(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Activity

public:
	virtual void ActivateAnomaly_Implementation(uint8 Anomaly_ID) override;

#pragma endregion

#pragma region Blur

protected:
	void ShowBlurWiget();

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUI_PopUp_Base> UI_Blur;

	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> Sound_Blur;

#pragma endregion

};