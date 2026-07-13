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

#pragma region Reference

private:
	UPROPERTY()
	TWeakObjectPtr<class UUI_Interact> UI_Interact;

#pragma endregion

#pragma region Interact

public:
	void ShowInteracting(bool bIsShow);
	bool CanInteract() { return !List_Interact.IsEmpty() && !bIsInteracted; }
	void TryChangeIndex(bool bUp);
	void Interact(class AEHCharacter* Interacter);
	FInteractInfo GetSelectedInteractInfo();
	void RestoreInteract() { bIsInteracted = false; }
	void DeactiveInteract() { bIsInteracted = true; }

private:
	void ShowDescriptionWidget(bool bIsShow);
	FText GetDescription() { return List_Interact[CurrentIndex].Description; }
	void ChangeIndex(bool bUp);
	bool HasManyInteracting() { return List_Interact.Num() > 1; }

public:
	UPROPERTY(EditAnywhere, Category = "Interact")
	TArray<FInteractInfo> List_Interact;

private:
	bool bIsInteracted = false;
	int8 CurrentIndex = 0;
	bool bChangingIndex = false;

#pragma endregion

#pragma region Highlight

public:
	void ShowInteractingHighlight(bool bActive);

#pragma endregion

};