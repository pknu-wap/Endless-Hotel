// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_ShelfBook.generated.h>

class UBoxComponent;
class UStaticMeshComponent;
class USceneComponent;
class USoundWave;
class UAudioComponent;
class UPrimitiveComponent;

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_ShelfBook : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_ShelfBook(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> TriggerBox;

	UPROPERTY()
	TArray<TObjectPtr<UStaticMeshComponent>> BookComps;

	UPROPERTY()
	TObjectPtr<UAudioComponent> AC;

#pragma endregion

#pragma region Reset

public:
	virtual void Reset() override;

#pragma endregion

#pragma region Fall

public:
	void ActiveTrigger();
	void FallSound();

protected:
	UFUNCTION()
	void ShelfBooksFall();

protected:
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> Sound_BookDrop;

	bool bIsFallen = false;

#pragma endregion

#pragma region Restore

public:
	virtual void StartRestoring(float Duration = 2.5f) override;

protected:
	UPROPERTY()
	TArray<TObjectPtr<USceneComponent>> OriginalBookParents;

	TArray<FTransform> OriginalBookRelativeTransforms;

#pragma endregion
};
