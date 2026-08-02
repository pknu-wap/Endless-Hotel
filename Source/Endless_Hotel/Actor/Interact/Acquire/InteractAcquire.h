// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Actor/Interact/InteractBase.h"
#include "Type/UI/Type_UI.h"
#include <CoreMinimal.h>
#include <InteractAcquire.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AInteractAcquire : public AInteractBase
{
	GENERATED_BODY()

#pragma region Interact

public:
	virtual void Interact_Implementation(AEHCharacter* Interacter) override;

#pragma endregion

#pragma region Acquire

protected:
	virtual void SaveAcquireData() PURE_VIRTUAL(&ThisClass::SaveAcquireData, );

#pragma endregion

#pragma region Move

protected:
	void MoveToPlayerCamera(AEHCharacter* Interacter);

	UFUNCTION()
	void OnMoveCompleted();

protected:
	UPROPERTY(EditAnywhere, Category = "Move")
	float ForwardLength = 10.f;

	UPROPERTY(EditAnywhere, Category = "Move")
	float UpLength = -3.f;

	UPROPERTY(EditAnywhere, Category = "Move")
	FRotator RotationOffset;

#pragma endregion

#pragma region Setting

protected:
	UPROPERTY(EditAnywhere, Category = "Setting")
	FText AcquireInfo;

#pragma endregion

};