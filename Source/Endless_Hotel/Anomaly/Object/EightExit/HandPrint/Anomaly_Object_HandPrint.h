// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/EightExit/Anomaly_Object_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_HandPrint.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_HandPrint : public AAnomaly_Object_EightExit
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_HandPrint(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Cong

public:
	void ReserveCongCong();

protected:
	void ShowHandPrint();
	void TurnOffLights();

public:
	static bool bIsFirstHandPrint;

protected:
	UPROPERTY(EditAnywhere, Category = "Anomaly")
	uint8 HandPrintIndex = 0;

	UPROPERTY(EditAnywhere, Category = "Decal")
	TObjectPtr<class UDecalComponent> Decal_HandPrint;

	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> Sound_First;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> Sound_Default;

#pragma endregion

};