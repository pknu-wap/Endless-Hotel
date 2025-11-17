// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Anomaly_Object_HandPrint.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_HandPrint : public AAnomaly_Object_Base
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_HandPrint(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(EditAnywhere)
	uint8 HandPrintIndex = 0;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UDecalComponent> Decal_HandPrint;

	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC;

#pragma endregion

#pragma region Cong

public:
	void StartCongCong(float& NextCong);

protected:
	static bool bIsFirstHandPrint;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USoundWave> Sound_First;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USoundWave> Sound_Default;

#pragma endregion

};