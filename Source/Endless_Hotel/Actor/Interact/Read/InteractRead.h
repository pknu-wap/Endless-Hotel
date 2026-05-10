// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Actor/Interact/InteractBase.h"
#include <CoreMinimal.h>
#include <InteractRead.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AInteractRead : public AInteractBase
{
	GENERATED_BODY()

#pragma region Interact

public:
	virtual void Interact_Implementation(AEHCharacter* Interacter) override;

#pragma endregion

#pragma region Camera

public:
	void PossessCamera(bool bIsReading);

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UUI_Base> UI_Read_Class;

#pragma endregion

};