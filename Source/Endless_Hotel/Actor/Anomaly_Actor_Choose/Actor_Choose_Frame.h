// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Actor/EHActor.h"
#include <CoreMinimal.h>
#include <Actor_Choose_Frame.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AActor_Choose_Frame : public AEHActor
{
	GENERATED_BODY()

public:
	AActor_Choose_Frame(const FObjectInitializer& ObjectInitializer);

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
