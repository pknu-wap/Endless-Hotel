// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Component/EHComponent.h"
#include <CoreMinimal.h>
#include <ReadComponent.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UReadComponent : public UEHComponent
{
	GENERATED_BODY()

#pragma region Reference

private:
	void SetReferenceObject(class AEHCharacter* Interacter, AActor* Target);

private:
	UPROPERTY()
	TWeakObjectPtr<AActor> TargetObject;

	UPROPERTY()
	TWeakObjectPtr<class AEHCharacter> Player;

	UPROPERTY()
	TWeakObjectPtr<class USpringArmComponent> Comp_SpringArm;

	UPROPERTY()
	TWeakObjectPtr<class UInteractComponent> Comp_Interact;

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UUI_Base> UI_Read_Class;

#pragma endregion

#pragma region Move

public:
	void MoveCameraToTarget(class AEHCharacter* Interacter, AActor* Target);
	void RestoreCamera();

private:
	UFUNCTION()
	void OnMoveCompleted();

	UFUNCTION()
	void OnRestoreCompleted();

private:
	FVector OriginalLoc;
	FRotator OriginalRot;

#pragma endregion

};