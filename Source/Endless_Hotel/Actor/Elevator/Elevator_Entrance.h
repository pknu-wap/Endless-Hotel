// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Actor/EHActor.h"
#include "Elevator_Entrance.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AElevator_Entrance : public AEHActor
{
	GENERATED_BODY()

#pragma region Base
	
public:
	AElevator_Entrance(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category="Entrance")
	TObjectPtr<UStaticMeshComponent> Entrance;
	
#pragma endregion

#pragma region Trigger

public:
	void SetTriggerActive();
	void ResetTrigger();

protected:
	UFUNCTION()
	virtual void OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditAnywhere, Category = "TakeOffTrigger")
	TObjectPtr<class UBoxComponent> TakeOff_Trigger;

	UPROPERTY(EditAnywhere, Category = "Elevator")
	TWeakObjectPtr<class AElevator> Elevator;

	UPROPERTY(EditAnywhere, Category = "Movement|Door")
	float DoorDelay = 2.0f;

#pragma endregion

};