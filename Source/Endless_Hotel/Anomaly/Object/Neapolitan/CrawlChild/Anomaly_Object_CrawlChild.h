// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_CrawlChild.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_CrawlChild : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class UAudioComponent> AC;

public:
	AAnomaly_Object_CrawlChild(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region CrawlChild

protected:
	UPROPERTY(EditAnywhere, Category = "Move")
	float LockSpeed = 100.f;

	UPROPERTY(EditAnywhere, Category = "Socket")
	FName SocketName = TEXT("CrawlChild");

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> Sound_Child;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> TriggerBox;

	UPROPERTY(EditAnywhere)
	FTransform TriggerBox_Transform;

	bool bShouldDie = false;

public:
	void ActivePlayTrigger();

protected:
	UFUNCTION()
	virtual void OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void AttatchChildToPlayer();
	void ApplyBackwardsPenalty();

#pragma endregion

#pragma region Subtitle

public:
	void ShowSubTitle();

#pragma endregion

};
