// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Actor/Interact/InteractBase.h"
#include <CoreMinimal.h>
#include <Manual.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AManual : public AInteractBase
{
	GENERATED_BODY()

#pragma region Base

public:
	AManual(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Interact

public:
	virtual void Interact_Implementation(AEHCharacter* Interacter) override;

#pragma endregion

#pragma region Component

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UReadComponent> Comp_Read;

#pragma endregion

};