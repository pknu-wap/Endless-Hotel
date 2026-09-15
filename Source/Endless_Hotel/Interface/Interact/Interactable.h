// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <UObject/Interface.h>
#include <Interactable.generated.h>

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class ENDLESS_HOTEL_API IInteractable
{
	GENERATED_BODY()

public:
	virtual void Interact(class AEHCharacter* Interacter) PURE_VIRTUAL(&ThisClass::Interact, );
};