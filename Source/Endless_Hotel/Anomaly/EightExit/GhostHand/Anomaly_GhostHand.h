// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Event_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_GhostHand.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_GhostHand : public AAnomaly_Event_EightExit
{
	GENERATED_BODY()

#pragma region Base
public:
	AAnomaly_GhostHand(const FObjectInitializer& ObjectInitializer);
#pragma endregion

#pragma region Acitvity
public:
	virtual void SetAnomalyState() override;
#pragma endregion

#pragma region GhostHand
public:
	void AttachGhostHand();

protected:
	UPROPERTY(EditAnywhere, Category = "GhostHand")
	TObjectPtr<UStaticMeshComponent> SM_Hand;

	FName AttachSoketName = TEXT("Hand_Leg");
	FTimerHandle ReapplySpeedHandle;
	const float LockWalkSpeed = 100.f;
	float ReapplyInterval = 0.05f;
#pragma endregion

#pragma region RunLock
public:
	bool bLockRun = true;
#pragma endregion
};