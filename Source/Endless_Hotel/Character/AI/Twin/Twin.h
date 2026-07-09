// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Character/AI/BaseAI.h"
#include <CoreMinimal.h>
#include <Twin.generated.h>

#pragma region Declare

UENUM()
enum class ETwinState : uint8
{
	Frozen,
	Moving
};

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API ATwin : public ABaseAI
{
	GENERATED_BODY()
	
#pragma region Base

public:
	ATwin(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

public:
	UPROPERTY(EditAnywhere, Category = "State")
	ETwinState CurrentState = ETwinState::Frozen;

	float DetectDistance;

public:
	void SetTwinState(ETwinState NewState);
	ETwinState GetTwinState() const { return CurrentState; }

#pragma region Trigger

protected:
	UFUNCTION()
	void OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditAnywhere, Category = "TriggerBox")
	TObjectPtr<class UBoxComponent> TriggerBox;

#pragma endregion

};