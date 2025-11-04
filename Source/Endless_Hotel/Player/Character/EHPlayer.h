// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Character/Character/EHCharacter.h"
#include "Delegates/DelegateCombinations.h"
#include "EHPlayer.generated.h"

#pragma region Declare

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCanInteract, bool, bCanInteract);

#pragma endregion

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

#pragma region Delegate

public:
	FCanInteract CanInteract;

#pragma endregion

};