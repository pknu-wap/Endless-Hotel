// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Actor/Interact/Read/InteractRead.h"
#include <CoreMinimal.h>
#include <NoteBook.generated.h>

UCLASS()
class ENDLESS_HOTEL_API ANoteBook : public AInteractRead
{
	GENERATED_BODY()

#pragma region Base

public:
	ANoteBook(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region NoteBook

public:
	void TurnOverPage(bool bLeft);

	float GetAnimationLength(bool bLeft);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> SKM_NoteBook;

	UPROPERTY(EditAnywhere, Category = "NoteBook")
	TObjectPtr<UAnimMontage> AM_LeftToRight;

	UPROPERTY(EditAnywhere, Category = "NoteBook")
	TObjectPtr<UAnimMontage> AM_RightToLeft;

#pragma endregion

#pragma region Description

public:
	void ShowDescription(bool bShow, uint8 Index);

private:
	void FindDescription();

private:
	UPROPERTY()
	TArray<TObjectPtr<UStaticMeshComponent>> SM_Descriptions;

#pragma endregion

};