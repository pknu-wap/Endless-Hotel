// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Component/EHComponent.h"
#include "Type/Interact/Type_Interact.h"
#include <CoreMinimal.h>
#include <InteractComponent.generated.h>

#pragma region Declare

#define HIGHLIGHT_TAG TEXT("Highlight")

#pragma endregion

UCLASS(ClassGroup = (Custom))
class ENDLESS_HOTEL_API UInteractComponent : public UEHComponent
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Interact

public:
	void ShowInteracting(bool bIsShow);
	bool CanInteract() { return !List_Interact.IsEmpty() && List_Interact.IsValidIndex(CurrentIndex) && !List_Interact[CurrentIndex].bIsInteracted; }
	void Interact(class AEHCharacter* Interacter);
	FInteractInfo GetSelectedInteractInfo();
	void ActiveInteract(bool bActive);

private:
	bool HasManyInteracting() { return List_Interact.Num() > 1; }

private:
	UPROPERTY(EditAnywhere, Category = "Interact")
	TArray<FInteractInfo> List_Interact;

#pragma endregion

#pragma region Description

private:
	FText GetDescription() { return List_Interact[CurrentIndex].Description; }

private:
	UPROPERTY()
	TWeakObjectPtr<class UUI_Interact> UI_Description;

#pragma endregion

#pragma region Index

public:
	void TryChangeIndex(bool bUp);

private:
	void ChangeIndex(bool bUp);

private:
	int8 CurrentIndex = 0;
	bool bChangingIndex = false;

#pragma endregion

#pragma region Highlight

public:
	void ShowHighlight(bool bActive);

#pragma endregion

};