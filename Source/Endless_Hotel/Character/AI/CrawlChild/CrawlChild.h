// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Character/AI/BaseAI.h"
#include <CoreMinimal.h>
#include <CrawlChild.generated.h>

UCLASS()
class ENDLESS_HOTEL_API ACrawlChild : public ABaseAI
{
	GENERATED_BODY()
	
#pragma region Base

public:
	ACrawlChild(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Setting

public:
	void SetOwnerAnomalyEvent(class AAnomaly_CrawlChild* NewEvent);

public:
	TWeakObjectPtr<class AAnomaly_Object_WChair>WheelChairObjectRef;

protected:
	UPROPERTY()
	TWeakObjectPtr<class AAnomaly_CrawlChild> OwnerAnomalyEvent;

#pragma endregion

#pragma region CatchPlayer

protected:
	UPROPERTY(EditAnywhere, Category = "Socket")
	FName SocketName = TEXT("CrawlChild");

	UPROPERTY(EditAnywhere, Category = "Move")
	float LockSpeed = 100.f;

	UPROPERTY(EditAnywhere, Category = "Socket|Setting")
	FTransform SocketSetting;

private:
	bool bIsAttached = false;
	TObjectPtr<class USkeletalMeshComponent> AttachedPlayerMesh = nullptr;
	FQuat FixedWorldRotation = FQuat::Identity;

public:
	void DetachFromPlayer();

#pragma endregion

#pragma region Trigger

protected:
	UPROPERTY(EditAnywhere, Category = "TriggerBox")
	TObjectPtr<class UBoxComponent> TriggerBox;

protected:
	UFUNCTION()
	void OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

#pragma endregion

};