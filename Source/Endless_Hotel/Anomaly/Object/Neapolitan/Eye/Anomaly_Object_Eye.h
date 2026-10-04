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
	AAnomaly_Object_Eye(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void InitializeOnAnomalySpawned() override;
	
#pragma endregion
	
#pragma region EyeAppear
	
public:
	void StartEyeAppear();
	void ShowEye();
	
private:
	void StartDrop();
	void SettleEye() const;
	void StartEyeFloating() const;
	
	UFUNCTION()
	void OnFloatUpdate(float Alpha) const;
	
	UFUNCTION()
	void OnFloatFinished();
	
protected:
	UPROPERTY(EditAnywhere, Category = "Eye")
	int32 EyeIndex = 0;
	
	UPROPERTY(EditAnywhere, Category="Eye")
	float AppearStartDelay = 1.f;
	
	UPROPERTY(EditAnywhere, Category="Eye")
	float AppearInterval = 0.15f;
	
	UPROPERTY(EditAnywhere, Category="Eye|Drop")
	bool bDropOnAppear = false;
	
	UPROPERTY(EditAnywhere, Category="Eye|Drop")
	FVector DropOffset;
	
	UPROPERTY(EditAnywhere, Category="Eye|Drop")
	float RollImpulse = 150.f;
	
	UPROPERTY(EditAnywhere, Category="Eye|Drop")
	float SettleTimeout = 5.f;
	
	UPROPERTY(EditAnywhere, Category="Eye|Drop")
	float FloatDuration = 1.5f;
	
	UPROPERTY(EditAnywhere, Category="Eye|Drop")
	FVector HomeLocation;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UTimelineComponent> FloatTimeline;
	
	UPROPERTY(EditAnywhere, Category="Eye|Drop")
	TObjectPtr<UCurveFloat> FloatCurve;
	
private:
	FTimerHandle AppearHandle;
	FTimerHandle SettleHandle;
	float FloatElapsed = 0.f;
	
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