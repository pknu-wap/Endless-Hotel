// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Anomaly_Object_Base.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Twin.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Twin : public AAnomaly_Object_Base
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomaly_Object_Twin(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Activity

public:
	void TwinReveal();

protected:
	UPROPERTY(EditAnywhere, Category = "Anomaly|Twin")
	FVector FirstSpawnLocation;

	UPROPERTY(EditAnywhere, Category = "Anomaly|Twin")
	FVector ActiveSpawnLocation;


#pragma endregion

#pragma region Twin

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Twin")
	TObjectPtr<UStaticMeshComponent> TwinMesh;

#pragma endregion
};
