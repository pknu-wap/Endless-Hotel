// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Anomaly_Object_ShelfBook.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_ShelfBook : public AAnomaly_Object_Base
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_ShelfBook(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	TObjectPtr<USceneComponent>Root;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent>TriggerBox;

	UPROPERTY()
	TArray<TObjectPtr<UStaticMeshComponent>>BookComps;

#pragma endregion

#pragma region Fall

public:
	void ActiveTrigger();

protected:
	UFUNCTION()
	void OnBooksFallRange(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	void BooksFall();

protected:
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> Sound_BookDrop;

	bool bIsFallen=false;

#pragma endregion
};
