// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Actor/EHActor.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_HandPrint.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_HandPrint : public AEHActor
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_HandPrint(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region HandPrint

public:
	void ShowHandPrint(uint8 Index);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UDecalComponent> Decal_HandPrint;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> AC;

	UPROPERTY(EditAnywhere, Category = "HandPrint")
	TObjectPtr<class USoundWave> SW_First;

#pragma endregion

};