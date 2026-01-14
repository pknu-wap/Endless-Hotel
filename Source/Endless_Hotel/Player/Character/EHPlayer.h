// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Character/Character/EHCharacter.h"
#include "Type/Player/Type_Death.h"
#include <CoreMinimal.h>
#include <Delegates/DelegateCombinations.h>
#include <EHPlayer.generated.h>

#pragma region Declare

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCanInteract, bool, bCanInteract);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDieDelegate, const EDeathReason&, DeathReason);

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

#pragma region Interact

public:
	FCanInteract CanInteract;

#pragma endregion

#pragma region Death

protected:
	UFUNCTION()
	void DiePlayer(const EDeathReason& DeathReason);

public:
	FDieDelegate DieDelegate;

protected:
	UPROPERTY(EditAnywhere)
	TMap<EDeathReason, TObjectPtr<class UAnimMontage>> DeathAnims;

#pragma endregion

};