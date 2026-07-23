// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Doll.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Doll : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_Doll(const FObjectInitializer& ObjectInitializer);
	
#pragma endregion

#pragma region Reset

public:
	virtual void Reset() override;

#pragma endregion

#pragma region Doll

public:
	void ActivateDoll_Show();

#pragma endregion

#pragma region Interact

public:
	virtual void Interact_Implementation(AEHCharacter* Interacter) override;

#pragma endregion

#pragma region Burn

protected:
	void StartBurning();
	void SetupBurnTargets();

private:
	void BurnTick();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> AC;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UNiagaraComponent> Niagara_Fire;

	UPROPERTY(EditAnywhere, Category = "Burn")
	TObjectPtr<UTexture> DissolveTexture;

	UPROPERTY(EditAnywhere, Category = "Burn")
	FLinearColor EdgeColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, Category = "Burn")
	float ColorBoost = 1.f;

private:
	UPROPERTY()
	TArray<TObjectPtr<UMaterialInstanceDynamic>> MID_Burn;

	FTimerHandle BurnHandle;

	float BurnCurrentTime = 0.f;

#pragma endregion

#pragma region Coming

public:
	void SpawnComingDolls();

private:
	void TryBurnComingDolls();

protected:
	UPROPERTY(EditAnywhere, Category = "Coming")
	TSubclassOf<class AComingDoll> ComingDollClass;

	UPROPERTY(EditAnywhere, Category = "Coming")
	TArray<FTransform> SpawnTrans;

private:
	UPROPERTY()
	TArray<TObjectPtr<class AComingDoll>> ComingDoll;

#pragma endregion

};