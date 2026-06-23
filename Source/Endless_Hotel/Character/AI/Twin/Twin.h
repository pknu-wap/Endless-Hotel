// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Character/AI/BaseAI.h"
#include <CoreMinimal.h>
#include <Twin.generated.h>

UENUM()
enum class ETwinState : uint8
{
	Frozen,
	Moving
};

UCLASS()
class ENDLESS_HOTEL_API ATwin : public ABaseAI
{
	GENERATED_BODY()

#pragma region Base

	virtual void BeginPlay() override;

#pragma endregion

public:
	void UpdateTwinState(bool bObserved);
	void FreezeWhenObserved();

#pragma region Trigger

protected:
	UFUNCTION()
	void OnKillTriggerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditAnywhere, Category = "KillTrigger")
	TObjectPtr<class UCapsuleComponent> KillTrigger;

	UPROPERTY(EditAnywhere, Category = "KillTrigger")
	float DefaultKillDistance;

	UPROPERTY(EditAnywhere, Category = "KillTrigger")
	float MinKillDistance;

#pragma endregion

public:
	UPROPERTY(EditAnywhere, Category = "Detect")
	float DetectDistance;

private:
	ETwinState CurrentState;
	FTimerHandle TwinTimerHandle;

};
