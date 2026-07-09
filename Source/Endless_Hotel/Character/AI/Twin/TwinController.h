// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Character/AI/BaseAIController.h"
#include <CoreMinimal.h>
#include <TwinController.generated.h>

UCLASS()
class ENDLESS_HOTEL_API ATwinController : public ABaseAIController
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void Tick(float DeltaTime) override;

#pragma endregion
};
