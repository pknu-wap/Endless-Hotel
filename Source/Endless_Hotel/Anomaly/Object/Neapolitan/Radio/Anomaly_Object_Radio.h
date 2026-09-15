// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Radio.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Radio : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_Radio(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Reset

public:
	virtual void Reset() override { StopRadio(); }

#pragma endregion

#pragma region Sound

protected:
	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> Sound_Radio;

#pragma endregion

#pragma region Radio

public:
	UFUNCTION()
	void PointerMoving();

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> SM_Radio_Pointer;

#pragma endregion

#pragma region Move

protected:
	void FinishMove();
	void StopRadio();

#pragma endregion

#pragma region PointerTimeline

protected:
	UFUNCTION()
	void UpdatePointerSpin(float Value);

protected:
	UPROPERTY()
	TObjectPtr<class UTimelineComponent> Timeline_PointerSpin;

	UPROPERTY(EditAnywhere, Category = "Radio")
	TObjectPtr<class UCurveFloat> CV_PointerSpin;

	FRotator OriginalPointerRotation;

#pragma endregion

#pragma region Interact

protected:
	virtual void Interact(class AEHCharacter* Interacter) override;
};