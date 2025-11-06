// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Anomaly_Object_Painting.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Painting : public AAnomaly_Object_Base
{
	GENERATED_BODY()
#pragma region Base

public:
	AAnomaly_Object_Painting(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnyWhere, Category = "Painting")
	TObjectPtr<class UStaticMeshComponent> Mesh_Painting;

	UPROPERTY(EditAnyWhere, Category = "Eye")
	TObjectPtr<class UStaticMeshComponent> Mesh_LeftEye;

	UPROPERTY(EditAnyWhere, Category = "Eye")
	TObjectPtr<class UStaticMeshComponent> Mesh_RightEye;

#pragma endregion

#pragma region EyeMove

public:
	UFUNCTION(BlueprintCallable)
	void EyeFollowing();

#pragma endregion

};
