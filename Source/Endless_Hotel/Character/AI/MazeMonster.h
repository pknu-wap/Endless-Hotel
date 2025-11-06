// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Character/Character/EHCharacter.h"
#include "MazeMonster.generated.h"


UCLASS()
class ENDLESS_HOTEL_API AMazeMonster : public AEHCharacter
{
	GENERATED_BODY()

#pragma region Base

public:
	AMazeMonster(const FObjectInitializer& ObjectInitializer);

#pragma endregion

};
