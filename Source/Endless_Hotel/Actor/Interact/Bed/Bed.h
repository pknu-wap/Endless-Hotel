// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Actor/Interact/InteractBase.h"
#include "Component/Bed/BedDirectionComponent.h"
#include <CoreMinimal.h>
#include <Bed.generated.h>

enum class EGameProgression : uint8;

UCLASS()
class ENDLESS_HOTEL_API ABed : public AInteractBase
{
	GENERATED_BODY()
	
#pragma region Base

public:
	ABed(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

#pragma endregion

#pragma region Interact

public:
	virtual void Interact(AEHCharacter* Interacter) override;

#pragma endregion

#pragma region Progression

private:
	void OnChangedProgression(EGameProgression Target);

#pragma endregion

#pragma region Component

private:
	UPROPERTY()
	TObjectPtr<UBedDirectionComponent> Comp_Direction;

#pragma endregion

#pragma region Rest

private:
	void StartRest();
	void StartWakeUp();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Rest")
	TArray<FBedDirectionInfo> RestInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Rest")
	TArray<FBedDirectionInfo> WakeInfo;

#pragma endregion

};