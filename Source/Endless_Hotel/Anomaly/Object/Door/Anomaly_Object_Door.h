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

	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC_DoorMove;

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

#pragma region DoorClose

public:
	void StartDoorClose();

protected:
	UPROPERTY()
	TObjectPtr<class UBoxComponent> TriggerBox_Door5;

	UPROPERTY()
	TObjectPtr<class UBoxComponent> TriggerBox_Door8;

protected:
	UPROPERTY()
	TWeakObjectPtr<class AAnomaly_Object_Door> Door8Cached;

protected:
	bool bDoor16Initialized = false;

protected:
	void SetupDoor16Triggers();
	void SetTriggerEnabled(class UBoxComponent* TriggerBox, bool bEnabled);
	bool IsPlayerCharacter(AActor* OtherActor) const;

	class AAnomaly_Object_Door* FindDoorByIndex(int32 Index) const;

	UPROPERTY()
	TWeakObjectPtr<class AAnomaly_Object_Door> Door8ObjectCached;

	UPROPERTY(EditAnywhere, Category = "Anomaly|Sound")
	TObjectPtr<class USoundWave> Sound_DoorOpen;

	UPROPERTY(EditAnywhere, Category = "Anomaly|Sound")
	TObjectPtr<class USoundWave> Sound_DoorClose;

protected:
	UFUNCTION()
	void OnDoor16Trigger5Overlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnDoor16Trigger8Overlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

#pragma endregion

#pragma region DoorRotation
public:
	void SetDoorRotationZ(float NewZ);

	void PlayDoorRotationDeltaSquence(const TArray<float>& DeltaList, float StepInterval);

protected:
	FTimerHandle RotationStepHandle;
	float RotationBaseZ = 0.f;
	float RotationStepInterval = 0.12f;
	int32 RotationStepIndex = 0;
	TArray<float> RotationDeltaList;

#pragma endregion
};