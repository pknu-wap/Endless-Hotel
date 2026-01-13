// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include "Anomaly_GhostHand.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_GhostHand : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()

#pragma region Base
public:
	AAnomaly_GhostHand(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
#pragma endregion

#pragma region Activity
public:
	virtual void ActivateAnomaly() override;
#pragma endregion

#pragma region GhostHand
protected:
	UPROPERTY(VisibleAnywhere, Category="GhostHand|Component")
	TObjectPtr<class UStaticMeshComponent> SM_Hand;

	UPROPERTY(EditAnywhere, Category = "GhostHand|Attach")
	FName AttachSocketName = TEXT("Hand_Leg");

	UPROPERTY(EditAnywhere, Category = "GhostHand|Attach")
	FVector AttachLocationOffset = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "GhostHand|Attach")
	FRotator AttachRotationOffset = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, Category = "GhostHand|Attach")
	FVector AttachScale = FVector(1.f, 1.f, 1.f);

	UPROPERTY(EditAnywhere, Category = "GhostHand|Time")
	float StartDelay = 0.5f;

	void ExecuteGhostHand();

	FTimerHandle StartDelayHandle;
#pragma endregion

#pragma region RunLock
	UPROPERTY(EditAnywhere, Category = "GhostHand|RunLock")
	bool bLockRun = true;

	UPROPERTY(EditAnywhere, Category = "GhostHand|RunLock")
	float LockedWalkSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = "GhostHand|RunLock")
	float ReapplyInterval = 0.05f;

	FTimerHandle ReapplySpeedHandle;

	bool bSaved = false;
	float SavedMaxWalkSpeed = 0.f;
	bool SavedCanRun = true;

	void ApplyRunLock();
	void ClearRunLock();
#pragma endregion
};