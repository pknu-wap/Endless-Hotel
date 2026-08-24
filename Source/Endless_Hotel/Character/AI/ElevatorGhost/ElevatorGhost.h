// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Character/AI/BaseAI.h"
#include <CoreMinimal.h>
#include <ElevatorGhost.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AElevatorGhost : public ABaseAI
{
	GENERATED_BODY()

#pragma region Base

public:
	AElevatorGhost(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void Tick(float Deltatime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Eye")
	TObjectPtr<UStaticMeshComponent> EyeMesh;

#pragma endregion

#pragma region Attack

private:
	void AttackPlayer();

#pragma endregion

#pragma region Look

private:
	void UpdateLookAtPlayer(float DeltaTime);

public:
	void SetShouldLookAtPlayer(bool bValue) { bShouldLookAtPlayer = bValue; }

private:
	UPROPERTY(EditAnywhere, Category = "Look")
	float TurnInterpSpeed = 3.f;

	bool bShouldLookAtPlayer = false;

#pragma endregion

};