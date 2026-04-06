// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Actor/EHActor.h"
#include "Type/Anomaly/Type_AnomalyName.h"
#include "Type/Interact/Type_Interact.h"
#include <CoreMinimal.h>
#include <Anomaly_Event.generated.h>

#pragma region Declare

class AAnomaly_Object_Base;

#pragma endregion

UCLASS(Blueprintable, BlueprintType)
class ENDLESS_HOTEL_API AAnomaly_Event : public AEHActor
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Event(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region ObjectLinker

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anomaly|Linker")
	TArray<AActor*> LinkedObjects;

	TArray<TObjectPtr<AAnomaly_Object_Base>> TargetAnomalyObjects;

#pragma endregion

#pragma region Anomaly

protected:
	virtual void StartAnomalyAction();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anomaly|ID")
	uint8 AnomalyID = -1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anomaly|ID")
	EAnomalyName AnomalyName;

	UPROPERTY(EditAnywhere, Category = "Anomaly|Object")
	bool bIsRuntimeSpawned = false;

	UPROPERTY(EditAnywhere, Category = "Anomaly|Object")
	bool bIsEightExitObject = false;

	UPROPERTY(EditAnywhere, Category = "Anomaly|Object")
	FTransform ObjectTransform = FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector(1, 1, 1));

protected:
	TFunction<void(class AAnomaly_Object_Base*)> AnomalyAction;

#pragma endregion

#pragma region Verdicts

public:
	virtual void InteractSolveVerdict();   //상호작용 이상현상 판정

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Verdict")
	bool bIsSolved = false;

protected:
	UFUNCTION()
	void SetVerdictMode(EAnomalyVerdictMode NewMode);

#pragma endregion

#pragma region Activity

public:
	virtual void SetAnomalyState();

	UFUNCTION()
	virtual void DisableAnomaly() {}

#pragma endregion

#pragma region Trigger

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> TriggerBox;

	UPROPERTY(EditAnywhere, Category = "Trigger")
	FTransform Transform_TriggerBox;

#pragma endregion

#pragma region StartType

protected:
	// 트리거
	virtual void ActiveTrigger();

	UFUNCTION()
	virtual void OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 타이머 & 즉발
	virtual void ScheduleAnomaly(float delay = 0.01f);

#pragma endregion

#pragma region Transform

public:
	UPROPERTY(EditAnywhere, Category = "Start")
	FTransform PlayerStartTransform = FTransform(FRotator(0, 180, 0), FVector(-750, 570, 997), FVector(0.75f, 0.75f, 0.75f));

	UPROPERTY(EditAnywhere, Category = "Elevator")
	FName TargetElevatorID = "HotelElevator";

#pragma endregion

#pragma region Templete

protected:
	template<typename ObjectType>
	void SetupAnomalyAction(void (ObjectType::* SelectedFunc)(), EInteractType Interaction = EInteractType::None)
	{
		AnomalyAction = [SelectedFunc, Interaction](AAnomaly_Object_Base* Obj)
			{
				if (ObjectType* TargetObj = Cast<ObjectType>(Obj))
				{
					TargetObj->CorrectInteractType = Interaction;
					(TargetObj->*SelectedFunc)();
				}
			};
	}

#pragma endregion

};