// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Actor/Interact/InteractBase.h"
#include "Component/Bed/BedDirectionComponent.h"
#include <CoreMinimal.h>
#include <Bed_Ending.generated.h>

UCLASS()
class ENDLESS_HOTEL_API ABed_Ending : public AInteractBase
{
	GENERATED_BODY()

#pragma region Base

public:
	ABed_Ending(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Interact

public:
	virtual void Interact(AEHCharacter* Interacter) override;

#pragma endregion

#pragma region Component

private:
	UPROPERTY()
	TObjectPtr<UBedDirectionComponent> Comp_Direction;

#pragma endregion

#pragma region Sleep

private:
	void StartSleep();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Sleep")
	TArray<FBedDirectionInfo> SleepInfo;

#pragma endregion

};