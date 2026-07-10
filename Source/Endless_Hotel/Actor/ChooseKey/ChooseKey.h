// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Actor/EHActor.h"
#include <CoreMinimal.h>
#include <ChooseKey.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AChooseKey : public AEHActor
{
	GENERATED_BODY()

#pragma region Base

public:
	AChooseKey(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Key

protected:
	UPROPERTY(EditAnywhere, Category = "Key")
	TObjectPtr<class UStaticMesh> KeyMesh1;

	UPROPERTY(EditAnywhere, Category = "Key")
	TObjectPtr<class UStaticMesh> KeyMesh2;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Comp_Key;

#pragma endregion

};