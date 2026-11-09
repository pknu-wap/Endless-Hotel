// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Components/SceneComponent.h>
#include <BurnComponent.generated.h>

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ENDLESS_HOTEL_API UBurnComponent : public USceneComponent
{
	GENERATED_BODY()
	
#pragma region Base

public:
	UBurnComponent(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Burn

public:
	void StartBurning();
	void SetupBurnTargets(UMeshComponent* Object);
	void ResetBurning();

private:
	void BurnTick();

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAudioComponent> AC;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UNiagaraComponent> Niagara_Fire;

	UPROPERTY(EditDefaultsOnly, Category = "Burn")
	TObjectPtr<UTexture> DissolveTexture;

	UPROPERTY(EditDefaultsOnly, Category = "Burn")
	FLinearColor EdgeColor = FLinearColor::White;

	UPROPERTY(EditDefaultsOnly, Category = "Burn")
	float ColorBoost = 1.f;

	UPROPERTY()
	TWeakObjectPtr<UMeshComponent> BurnTarget;

	UPROPERTY()
	TArray<TObjectPtr<UMaterialInstanceDynamic>> MID_Burn;

	FTimerHandle BurnHandle;

	float BurnCurrentTime = 0.f;

#pragma endregion

};