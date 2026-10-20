// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_SignDrop.generated.h>

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
class ENDLESS_HOTEL_API AAnomaly_Object_SignDrop : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Init

public:
	virtual void InitializeOnAnomalySpawned() override;

#pragma endregion

#pragma region Interact

public:
	virtual void Interact(class AEHCharacter* Interacter) override;

#pragma endregion

#pragma region Sign

public:
	void ExecuteSignDrop();

private:
	UPROPERTY(EditAnywhere, Category = "Sign")
	TSubclassOf<UCameraShakeBase> CameraShakeClass;

	UPROPERTY(EditAnywhere, Category = "Sign")
	TObjectPtr<USoundWave> DropSound;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;

#pragma endregion 

};