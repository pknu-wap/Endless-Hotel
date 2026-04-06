// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Doll.generated.h>

class UStaticMeshComponent;
class AActor;

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Doll : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_Doll(const FObjectInitializer& ObjectInitializer);
	
#pragma endregion

#pragma region Doll

public:
	void ActivateDoll_Show();

#pragma endregion

#pragma region Interact

public:
	virtual void Interact_Implementation(AEHCharacter* Interacter) override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UNiagaraComponent> Niagara_Fire;

	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> Sound_Doll_Fire;

#pragma endregion

#pragma region Burn

protected:
	FTimerHandle BurnHandle;

	UPROPERTY(EditAnywhere, Category = "Burn")
	float BurnDuration = 5.f;

	float BurnCurrentTime = 0.f;

	bool bIsBurning = false;

	TWeakObjectPtr<UStaticMeshComponent> BurnMesh;
	TWeakObjectPtr<UNiagaraComponent> BurnNiagara;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> BurnMID = nullptr;

	FName Param_Alpha = TEXT("Alpha");
	FName Param_EdgeColor = TEXT("Edge Color");
	FName Param_DissolveTex = TEXT("Dissolve Texture");

	FName NiagaraVar_Alpha = TEXT("Alpha");
	FName NiagaraVar_EdgeColor = TEXT("EdgeColor");

	UPROPERTY(EditAnywhere, Category = "Burn")
	TObjectPtr<UTexture> DissolveTexture = nullptr;

	UPROPERTY(EditAnywhere, Category = "Burn")
	FLinearColor EdgeColor = FLinearColor::White; 

	UPROPERTY(EditAnywhere, Category = "Burn")
	float ColorBoost = 1.f;

protected:
	void SetupBurnTargets();
	void StartBurning(float Duration);
	void BurnTick();
	void FinishBurning();

#pragma endregion
};