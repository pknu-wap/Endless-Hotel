// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Anomaly/Event/EightExit/Anomaly_Event_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_CrawlChild.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_CrawlChild : public AAnomaly_Event_EightExit
{
	GENERATED_BODY()
	
#pragma region Activity

protected:
	virtual void SetAnomalyState() override;
	virtual void DisableAnomaly() override;

#pragma endregion

#pragma region Subtitle

public:
	UPROPERTY(EditAnywhere, Category = "SubTitle")
	TArray<FText> Subtitle;

public:
	void ShowSubTitle();

#pragma endregion

#pragma region AI

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCrawlChildSpawned, ACrawlChild*, SpawnedCrawlChild);
	FOnCrawlChildSpawned OnCrawlChildSpawned;

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<class ACrawlChild> CrawlChildClass;

	UPROPERTY(EditAnywhere, Category = "AI")
	FTransform AIStartTransform;

	TWeakObjectPtr<class ACrawlChild> CrawlChild;

protected:
	virtual void OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	void StartCrawlChild();

#pragma endregion

};
