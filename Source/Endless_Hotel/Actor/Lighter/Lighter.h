// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Actor/Interact/InteractBase.h"
#include <CoreMinimal.h>
#include <Lighter.generated.h>

UCLASS()
class ENDLESS_HOTEL_API ALighter : public AInteractBase
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Interact

public:
	virtual void Interact_Implementation(AEHCharacter* Interacter) override;

#pragma endregion

#pragma region Data

protected:
	void SaveTutorialData();

#pragma endregion

#pragma region Move

protected:
	void MoveToPlayerCamera(AEHCharacter* Interacter);

	UFUNCTION()
	void OnMoveCompleted();

#pragma endregion

};