// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Actor/EHActor.h"
#include "RoomSignActor.generated.h"

UCLASS()
class ENDLESS_HOTEL_API ARoomSignActor : public AEHActor
{
	GENERATED_BODY()
	
#pragma region Base

public:
	ARoomSignActor(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Mesh & Texture

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> SignMesh;

private:
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;

#pragma endregion

};