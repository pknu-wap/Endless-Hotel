// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Actor/EHActor.h"
#include <CoreMinimal.h>
#include <ChooseKey.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AChooseKey : public AEHActor
{
	GENERATED_BODY()

public:
	AChooseKey(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr <class UStaticMeshComponent> KeyMesh1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr <class UStaticMeshComponent> KeyMesh2;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Anomaly Data")
	int32 SelectedKeyIndex;
};
