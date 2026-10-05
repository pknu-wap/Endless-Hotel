// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Eye.generated.h>

enum class EDeathReason : uint8;

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Eye : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()
	
#pragma region Base
	
public:
	virtual void InitializeOnAnomalySpawned() override;
	
#pragma endregion
	
#pragma region EyeFocust
	
public:
	void StartEyeFocus();
	void StopEyeFocus(const EDeathReason& DeathReason);
	
private:
	UPROPERTY(EditAnywhere, Category = "EyeFocus")
	FRotator CorrectionRotation;
	
	FTimerHandle FocusHandle;
	
#pragma endregion
	
};