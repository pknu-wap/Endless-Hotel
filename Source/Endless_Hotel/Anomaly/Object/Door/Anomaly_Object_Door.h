// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Anomaly_Object_Door.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Door : public AAnomaly_Object_Base
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomaly_Object_Door(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh_Door;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh_Handle;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> TriggerBox;

#pragma endregion

#pragma region Shake

public:
	void ActiveTrigger();

protected:
	UFUNCTION()
	void OnDoorShakeRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void PlayShake_Handle();
	void PlayShake_Door();

	UFUNCTION()
	void ShakeDoor(float Value);

	UFUNCTION()
	void ShakeHandle(float Value);

protected:
	UPROPERTY()
	TObjectPtr<class UTimelineComponent> Timeline_Door;

	UPROPERTY()
	TObjectPtr<class UTimelineComponent> Timeline_Handle;

	UPROPERTY(EditAnywhere, Category = "Time")
	TObjectPtr<UCurveFloat> Curve_Door;

	UPROPERTY(EditAnywhere, Category = "Time")
	TObjectPtr<UCurveFloat> Curve_Handle;

	FVector Door_Origin;
	FVector Handle_Origin;

	const uint8 MaxShakeCount_Handle = 30;
	uint8 ShakeCount_Handle = 0;

	const uint8 MaxShakeCount_Door = 4;
	uint8 ShakeCount_Door = 0;

	FTimerHandle HandleHandle;
	FTimerHandle DoorHandle;

	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> Sound_DoorShake;

#pragma endregion

};