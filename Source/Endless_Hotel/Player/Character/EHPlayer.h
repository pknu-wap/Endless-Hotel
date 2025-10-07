// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Character/Character/EHCharacter.h"
#include "EHPlayer.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AEHPlayer : public AEHCharacter
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AEHPlayer(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Component

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UEHCameraComponent> Component_Camera;

#pragma endregion

};