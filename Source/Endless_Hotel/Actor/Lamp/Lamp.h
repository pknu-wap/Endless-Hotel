// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Actor/EHActor.h"
#include <CoreMinimal.h>
#include <Lamp.generated.h>

#define FLICKER_DURATION 0.001f;

UCLASS()
class ENDLESS_HOTEL_API ALamp : public AEHActor
{
	GENERATED_BODY()

#pragma region Base

public:
	ALamp(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

#pragma endregion

#pragma region Lamp

private:
	void TurnLampLight(bool bOn);

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UStaticMeshComponent> SM_Lamp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UPointLightComponent> PointLight;

	FTimerHandle LightHandle;

	UPROPERTY(EditAnywhere, Category = "Setting", meta = (ClampMin = "0.1"))
	float FlickerMin = 2.f;

	UPROPERTY(EditAnywhere, Category = "Setting", meta = (ClampMin = "0.1"))
	float FlickerMax = 20.f;

#pragma endregion

};