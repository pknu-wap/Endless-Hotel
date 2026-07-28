// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Actor/Interact/Acquire/InteractAcquire.h"
#include <CoreMinimal.h>
#include <Lighter.generated.h>

UCLASS()
class ENDLESS_HOTEL_API ALighter : public AInteractAcquire
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Acquire

protected:
	virtual void SaveAcquireData() override;

#pragma endregion

};