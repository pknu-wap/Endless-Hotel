// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Actor/Interact/InteractBase.h"
#include <CoreMinimal.h>
#include <NoteBook.generated.h>

UCLASS()
class ENDLESS_HOTEL_API ANoteBook : public AInteractBase
{
	GENERATED_BODY()

#pragma region Base

public:
	ANoteBook(const FObjectInitializer& ObjectInitializer);

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

#pragma region Page

public:
	void TurnOverPage(bool bLeft);

protected:
	UPROPERTY(EditAnywhere)
	FVector LeftPageLocation;

	UPROPERTY(EditAnywhere)
	FRotator LeftPageRotation;

	UPROPERTY(EditAnywhere)
	FVector RightPageLocation;

	UPROPERTY(EditAnywhere)
	FRotator RightPageRotation;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> SM_Paper;

private:
	FVector StartLocation;
	FVector EndLocation;

	FRotator StartRotation;
	FRotator EndRotation;

	FTimerHandle MoveHandle;

	float ElapsedTime = 0.f;

#pragma endregion

};