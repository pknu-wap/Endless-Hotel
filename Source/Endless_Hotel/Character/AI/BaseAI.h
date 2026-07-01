// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Character/EHCharacter.h"
#include <CoreMinimal.h>
#include <BaseAI.generated.h>

UCLASS()
class ENDLESS_HOTEL_API ABaseAI : public AEHCharacter
{
	GENERATED_BODY()

#pragma region Base

public:
	ABaseAI(const FObjectInitializer& ObjectInitializer);

#pragma endregion

};