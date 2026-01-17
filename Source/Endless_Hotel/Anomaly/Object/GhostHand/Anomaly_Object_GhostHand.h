// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Anomaly_Object_Base.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_GhostHand.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_GhostHand : public AAnomaly_Object_Base
{
	GENERATED_BODY()

#pragma region Base
public:
	AAnomaly_Object_GhostHand(const FObjectInitializer& ObjectInitializer);
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