// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/EightExit/Anomaly_Object_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Candle.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Candle : public AAnomaly_Object_EightExit
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_Candle(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Reset

public:
	virtual void Reset() override;

#pragma endregion

#pragma region Fall

public:
	void FallCandle();

private:
	UFUNCTION()
	void OnCandleDropped(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	UPROPERTY(EditAnywhere, Category = "Fall")
	FVector ImpulseDirection = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Fall")
	float ImpulseStrength = 0.f;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> Comp_Audio;

#pragma endregion

};