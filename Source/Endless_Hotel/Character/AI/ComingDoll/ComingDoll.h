// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Character/AI/BaseAI.h"
#include <CoreMinimal.h>
#include <ComingDoll.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AComingDoll : public ABaseAI
{
	GENERATED_BODY()

#pragma region Base

public:
	AComingDoll(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Burn

public:
	void StartBurning();

private:
	void SetupBurnTargets();
	void BurnTick();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> AC;

	UPROPERTY(EditAnywhere, Category = "Burn")
	TObjectPtr<UTexture> DissolveTexture;

	UPROPERTY(EditAnywhere, Category = "Burn")
	FLinearColor EdgeColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, Category = "Burn")
	float ColorBoost = 1.f;

private:
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> BurnDMI1;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> BurnDMI2;

	FTimerHandle BurnHandle;

	const float BurnDuration = 5.f;
	float BurnCurrentTime = 0.f;

#pragma endregion

#pragma region Death

private:
	UFUNCTION()
	void OnDeathTrigger(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCapsuleComponent> DeathTrigger;

#pragma endregion

};