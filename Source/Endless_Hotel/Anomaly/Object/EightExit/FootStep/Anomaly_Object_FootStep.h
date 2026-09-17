// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Actor/EHActor.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_FootStep.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_FootStep : public AEHActor
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomaly_Object_FootStep(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region FootStep

private:
	void DisappearFootStep();

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UDecalComponent> Decal_FootStep;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAudioComponent> AC;

	FTimerHandle DisappearHandle;

	FLinearColor Color_FootStep;

	const float TargetOpacity = 0.f;
	float CurrentOpacity = 1.f;

#pragma endregion

};