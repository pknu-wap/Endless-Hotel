// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include "Anomaly_Cong.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Cong : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Cong(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Trigger

protected:
	UFUNCTION()
	void OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY()
	TObjectPtr<class UBoxComponent> TriggerBox;

	UPROPERTY(EditAnywhere, Category = "Anomaly|Trigger")
	FTransform Transform_TriggerBox;

#pragma endregion

#pragma region Cong

protected:
	virtual void StartAnomalyAction() override;

protected:
	FTimerDelegate CongDelegate;
	FTimerHandle CongHandle;

	const uint8 MaxIndex = 50;
	uint8 CurrentIndex = 0;

	float NextCong = 2.9f;

#pragma endregion

};