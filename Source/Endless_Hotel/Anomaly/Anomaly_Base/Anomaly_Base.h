// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Anomaly_Base.generated.h"


//Forward Declaration
class UAnomalyProgressSubSystem;

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Base : public AActor
{
	GENERATED_BODY()

#pragma region Base

public:
	// Sets default values for this actor's properties
	AAnomaly_Base(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

#pragma endregion

#pragma region ID

public:
	UPROPERTY(BlueprintReadWrite, Category = "Anomaly|ID")
	int32 AnomalyID;

#pragma endregion

#pragma region Active DeActive

public:
	UPROPERTY(BlueprintReadWrite, Category = "Anomaly|Activate")
	bool bIsActive = false;

	UFUNCTION(BlueprintNativeEvent, Category = "Anomaly|Activate")
	void ActivateAnomaly();
	virtual void ActivateAnomaly_Implementation();

#pragma endregion

#pragma region Subsystem
protected:

	UFUNCTION(BlueprintCallable, Category = "Anomaly|Subsystem")
	void IsSolveAnomaly();

	UFUNCTION(BlueprintCallable, Category = "Anomaly|Subsystem")
	void IsNotSolveAnomaly();

	UFUNCTION(BlueprintCallable, Category = "Anomaly|Subsystem")
	void IsVerdictAnomaly();

#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

};
