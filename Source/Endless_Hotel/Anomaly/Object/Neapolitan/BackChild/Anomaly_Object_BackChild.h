// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_BackChild.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_BackChild : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class UAudioComponent> AC;

#pragma endregion

#pragma region BackChild

protected:
	UPROPERTY(EditAnywhere, Category = "Move")
	float LockSpeed = 100.f;

	UPROPERTY(EditAnywhere, Category = "Socket")
	FName SocketName = TEXT("BackChild");

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> Sound_Child;

public:
	void AttatchChildToPlayer();

#pragma endregion

};
