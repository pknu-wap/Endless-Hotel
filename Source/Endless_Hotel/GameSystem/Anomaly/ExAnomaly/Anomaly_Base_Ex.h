// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Anomaly_Base_Ex.generated.h"

UCLASS(Abstract, Blueprintable)
class ENDLESS_HOTEL_API AAnomaly_Base_Ex : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnomaly_Base_Ex(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Setting in BP Class Defaults, NEVER DUPLICATE
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anomaly")
	int32 DefaultID = -1;

	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	void StartAnomaly();
	virtual void StartAnomaly_Implementation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	

};
