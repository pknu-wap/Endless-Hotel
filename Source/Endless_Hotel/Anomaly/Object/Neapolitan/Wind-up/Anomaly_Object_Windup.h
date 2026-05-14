// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Neapolitan/Doll/Anomaly_Object_Doll.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Windup.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Windup : public AAnomaly_Object_Doll
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_Windup(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Sound

protected:
	UPROPERTY()
	TObjectPtr<UAudioComponent> AC_Windup;

	UPROPERTY()
	TObjectPtr<UAudioComponent> AC_Wrong;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundWave> Sound_Windup;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundWave> Sound_Wrong;

protected:
	void WindupPlay();

	void StopWindup();

	void WrongPlay();

#pragma endregion

#pragma region Interact

public:
	virtual void Interact_Implementation(class AEHCharacter* Interacter) override;

protected:
	enum class EWindupInteractStep : uint8
	{
		NeedStopSound,
		NeedBurn,
		Finished
	};

	UPROPERTY()
	EWindupInteractStep CurrentInteractStep = EWindupInteractStep::NeedStopSound;

#pragma endregion
};