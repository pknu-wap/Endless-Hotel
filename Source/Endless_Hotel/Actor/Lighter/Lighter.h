// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Actor/EHActor.h"
#include "Interface/Interact/Interactable.h"
#include <CoreMinimal.h>
#include <Lighter.generated.h>

UCLASS()
class ENDLESS_HOTEL_API ALighter : public AEHActor, public IInteractable
{
	GENERATED_BODY()

#pragma region Base

public:
	ALighter(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Lighter

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> SM_Lighter;

#pragma endregion

#pragma region Interact

public:
	virtual void Interact_Implementation(AEHCharacter* Interacter) override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UWidgetComponent> Component_Widget;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UInteractComponent> Component_Interact;

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