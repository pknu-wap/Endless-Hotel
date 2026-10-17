// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Character/AI/BaseAIController.h"
#include <CoreMinimal.h>
#include <ShadowMonsterController.generated.h>

#pragma region Declare

class AAnomaly_Object_Painting;

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API AShadowMonsterController : public ABaseAIController
{
	GENERATED_BODY()
	
#pragma region Base
	
public:
	void StartBind(AAnomaly_Object_Painting* OwnerPainting);
	
#pragma endregion
	
#pragma region Appear
	
public:
	void HandleMonsterAppear(bool bAppear);
	
protected:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	FTransform InitialTransform;
	
#pragma endregion
	
};