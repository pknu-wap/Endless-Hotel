// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Event/EightExit/Anomaly_Event_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Door.generated.h>

class UBoxComponent;
class AAnomaly_Object_Door;

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Door
	: public AAnomaly_Event_EightExit
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Door(
		const FObjectInitializer& ObjectInitializer
	);

#pragma endregion

#pragma region Activity

public:
	virtual void SetAnomalyState() override;

#pragma endregion

//#pragma region Trigger
//
//protected:
//	virtual void OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
//
//#pragma endregion
//
//#pragma region DoorSequence
//
//private:
//	enum class EDoorSequenceState : uint8
//	{
//		OpenDoor,
//		OpenHand,
//		CloseHandAndDoor,
//		Finished
//	};
//
//	void AdvanceDoorState();
//
//protected:
//	UPROPERTY(EditAnywhere, Category = "Door")
//	FTransform OpenDoorTriggerTrans;
//
//	UPROPERTY(EditAnywhere, Category = "Door")
//	FTransform OpenHandTriggerTrans;
//
//	UPROPERTY(EditAnywhere, Category = "Door")
//	FTransform CloseDoorTriggerTrans;
//
//private:
//	EDoorSequenceState CurrentDoorState = EDoorSequenceState::OpenDoor;
//
//#pragma endregion

};