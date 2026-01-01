// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Anomaly_Object_ShelfDoll.generated.h"

class UStaticMeshComponent;
class AActor;

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_ShelfDoll : public AAnomaly_Object_Base
{
	GENERATED_BODY()
	
#pragma region Base
public:
	AAnomaly_Object_ShelfDoll(const FObjectInitializer& ObjectInitializer);
#pragma endregion

#pragma region Doll
protected:
	UPROPERTY(EditAnywhere, Category = "ShelfDoll|Doll")
	TObjectPtr<UStaticMeshComponent> SM_Doll;

public:
	void ActivateDoll_Show();
#pragma endregion

#pragma region ShelfBook
protected:
	UPROPERTY(EditAnywhere, Category = "ShelfDoll|ShelfBook")
	TObjectPtr<AActor> BP_ShelfBookActor;

public:
	void ActivateShelfBook_Hide();
#pragma endregion

#pragma region Plant
protected:
	UPROPERTY(EditAnywhere, Category="ShelfDoll|Plant")
	TObjectPtr<AActor> BP_PlantBeforeActor;

public:
	void ActivatePlant_Hide();
#pragma endregion
};
