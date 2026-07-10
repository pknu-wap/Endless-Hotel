// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Event/EightExit/Anomaly_Event_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Twin.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Twin : public AAnomaly_Event_EightExit
{
	GENERATED_BODY()

#pragma region Activity

public:
	virtual void SetAnomalyState() override;
	virtual void DisableAnomaly() override;
	void StartTwin();

#pragma endregion

#pragma region TwinAISetting

public:
	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<class ATwin> TwinClass;

	UPROPERTY(EditAnywhere, Category = "AI")
	TArray<TWeakObjectPtr<class ATwin>> Twins;

	UPROPERTY(EditAnywhere, Category = "AI")
	TArray<FTransform> Transforms;

#pragma endregion

#pragma region Trigger

protected:
	virtual void OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

#pragma endregion

};