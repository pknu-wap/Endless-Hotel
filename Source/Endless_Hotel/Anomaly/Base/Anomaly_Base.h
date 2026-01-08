// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Actor/EHActor.h"
#include <CoreMinimal.h>
#include <Anomaly_Base.generated.h>

#pragma region Declare

class AAnomaly_Object_Base;

#pragma endregion

UCLASS(Blueprintable, BlueprintType)
class ENDLESS_HOTEL_API AAnomaly_Base : public AEHActor
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Base(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region ObjectLinker

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anomaly|Linker")
	TArray<AActor*> LinkedObjects;

#pragma endregion

#pragma region Anomaly

protected:
	virtual void StartAnomalyAction();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anomaly|ID")
	uint8 AnomalyID = -1;

protected:
	TFunction<void(class AAnomaly_Object_Base*)> AnomalyAction;

#pragma endregion

#pragma region Verdicts

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Verdict")
	bool bIsCorrectElevator = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Verdict")
	bool bIsSolved = false;

protected:

	UFUNCTION()
	void SetVerdictMode(EAnomalyVerdictMode NewMode);

#pragma endregion

#pragma region Activity

public:
	virtual void ActivateAnomaly(uint8 Anomaly_ID) PURE_VIRTUAL(AAnomaly_Base::ActivateAnomaly, ;);
	virtual void DisableAnomaly(uint8 Anomaly_ID) {}

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

	// 타이머
	virtual void StartDelay(float delay);

	// 초기
	virtual void StartImmediate();

#pragma endregion

};