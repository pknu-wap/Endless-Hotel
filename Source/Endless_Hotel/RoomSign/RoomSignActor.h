// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Actor/EHActor.h"
#include "RoomSignActor.generated.h"

#pragma region Declare

UENUM(BlueprintType)
enum class EFloorUV : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Floor1 = 1 UMETA(DisplayName = "Floor 1"),
	Floor2 = 2 UMETA(DisplayName = "Floor 2"),
	Floor3 = 3 UMETA(DisplayName = "Floor 3"),
	Floor4 = 4 UMETA(DisplayName = "Floor 4"),
	Floor5 = 5 UMETA(DisplayName = "Floor 5"),
	Floor6 = 6 UMETA(DisplayName = "Floor 6"),
	Floor7 = 7 UMETA(DisplayName = "Floor 7"),
	Floor8 = 8 UMETA(DisplayName = "Floor 8")
};

constexpr float GetOffsetG(EFloorUV Floor)
{
	switch (Floor)
	{
	case EFloorUV::Floor1: return -0.25f;
	case EFloorUV::Floor2: return -0.13f;
	case EFloorUV::Floor3: return -0.005f;
	case EFloorUV::Floor4: return  0.125f;
	case EFloorUV::Floor5: return  0.242f;
	case EFloorUV::Floor6: return  0.36f;
	case EFloorUV::Floor7: return  0.475f;
	case EFloorUV::Floor8: return  0.5975f;
	default:               return  0.0f;
	}
}

#pragma endregion

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