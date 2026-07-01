// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Twin.generated.h>

UENUM()
enum class ETwinState : uint8
{
	Frozen,
	Moving
};

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Twin : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_Twin(const FObjectInitializer& ObjectInitializer);
	void StartTwin();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	FTransform TwinTransform;

#pragma endregion

#pragma region Trigger

protected:
	UFUNCTION()
	virtual void OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditAnywhere, Category = "Trigger")
	TObjectPtr<class UBoxComponent> TriggerBox;

	UPROPERTY(EditAnywhere, Category = "Trigger")
	FVector KillTriggerSize = FVector(80.f, 80.f, 80.f);

	UPROPERTY(EditAnywhere, Category = "Trigger")
	FVector MinTriggerSize = FVector(20.f, 20.f, 20.f);

#pragma endregion

#pragma region Move

private:
	void FreezeWhenObserved();
	void UpdateTwinState(bool bObserved);
	void MoveTowardPlayer();

protected:
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = "Observe")
	float DetectDistance = 1500.f;

	ETwinState CurrentState = ETwinState::Frozen;
	FTimerHandle TwinTimerHandle;

#pragma endregion

};