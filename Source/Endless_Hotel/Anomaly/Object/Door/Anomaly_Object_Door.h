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

public:
	UPROPERTY(EditAnywhere)
	int32 DoorIndex = 0;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh_Door;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh_Handle;

	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC_Effect;

	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC_Voice;

#pragma endregion

#pragma region Shake

public:
	void PlayShake_Handle();

protected:
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

	UPROPERTY(EditAnywhere, Category = "Anomaly|Time")
	TObjectPtr<UCurveFloat> Curve_Door;

	UPROPERTY(EditAnywhere, Category = "Anomaly|Time")
	TObjectPtr<UCurveFloat> Curve_Handle;

	FVector Door_Origin;
	FVector Handle_Origin;

	FTimerHandle HandleHandle;
	FTimerHandle DoorHandle;

	const uint8 MaxShakeCount_Handle = 29;
	uint8 ShakeCount_Handle = 0;

	const uint8 MaxShakeCount_Door = 4;
	uint8 ShakeCount_Door = 0;

	UPROPERTY(EditAnywhere, Category = "Anomaly|Sound")
	TObjectPtr<class USoundWave> Sound_DoorShake;

	UPROPERTY(EditAnywhere, Category = "Anomaly|Sound")
	TArray<TObjectPtr<class USoundWave>> Sounds_Voice;

#pragma endregion

};