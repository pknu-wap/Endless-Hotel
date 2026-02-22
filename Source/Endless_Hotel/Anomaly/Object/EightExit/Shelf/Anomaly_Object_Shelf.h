// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/EightExit/Anomaly_Object_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Shelf.generated.h>

class UBoxComponent;
class UStaticMeshComponent;
class USceneComponent;
class USoundWave;
class UAudioComponent;
class UPrimitiveComponent;

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Shelf : public AAnomaly_Object_EightExit
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_Shelf(const FObjectInitializer& ObjectInitializer);

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

#pragma region Change

	UPROPERTY(EditAnywhere, Category = "Plant");
	TObjectPtr<class UStaticMeshComponent> SM_Plant;

	UPROPERTY(EditAnywhere, Category = "Plant");
	TObjectPtr<class UStaticMeshComponent> SM_AfterPlant;

public:
	void StartChange();

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

#pragma region DropSound

protected:
	UPROPERTY(EditAnywhere, Category = "Sound")
	TArray<TObjectPtr<USoundWave>> Sounds_BookDropRandom;

	UPROPERTY()
	TMap<UStaticMeshComponent*, float> BookLastSoundTimeMap;

	UPROPERTY()
	TMap<UStaticMeshComponent*, UAudioComponent*> BookAudioMap;

	UPROPERTY(EditAnywhere, Category = "Sound")
	float MinSoundInterval = 0.08f;

	UPROPERTY(EditAnywhere, Category = "Sound")
	int32 MaxDropSoundCount = 100;

	UPROPERTY()
	int32 CurrentDropSoundCount = 0;

	UFUNCTION()
	void OnBookHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void PlayRandomDropSound(UStaticMeshComponent* BookMesh, const FVector& WorldLocation, float DropImpulse);

#pragma endregion

};