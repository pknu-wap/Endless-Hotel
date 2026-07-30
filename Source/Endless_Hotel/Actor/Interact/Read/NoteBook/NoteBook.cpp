// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/Read/NoteBook/NoteBook.h"
#include <Components/WidgetComponent.h>

#pragma region Base

ANoteBook::ANoteBook(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SKM_NoteBook = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SKM_NoteBook"));
	SetRootComponent(SKM_NoteBook);

	Object->SetVisibility(false);

	Component_Widget->SetupAttachment(RootComponent);
}

#pragma endregion

#pragma region Page

void ANoteBook::TurnOverPage(bool bLeft)
{
	FindDescription();
	ShowDescription(false);

	UAnimInstance* AnimInstance = SKM_NoteBook->GetAnimInstance();
	UAnimMontage* TargetMontage = bLeft ? AM_LeftToRight : AM_RightToLeft;
	
	AnimInstance->Montage_Play(TargetMontage);

	const float AnimLength = TargetMontage->GetPlayLength();

	GetWorld()->GetTimerManager().SetTimer(ShowHandle, FTimerDelegate::CreateUObject(this, &ThisClass::ShowDescription, true), AnimLength, false);
}

float ANoteBook::GetAnimationLength(bool bLeft)
{
	return bLeft ? AM_LeftToRight->GetPlayLength() : AM_RightToLeft->GetPlayLength();
}

#pragma endregion

#pragma region Description

void ANoteBook::FindDescription()
{
	if (!SM_Descriptions.IsEmpty())
	{
		return;
	}

	TArray<UActorComponent*> Array = GetComponentsByTag(UStaticMeshComponent::StaticClass(), TEXT("Picture"));

	for (auto* Target : Array)
	{
		SM_Descriptions.Add(Cast<UStaticMeshComponent>(Target));
	}
}

void ANoteBook::ShowDescription(bool bShow)
{
	for (UStaticMeshComponent* Target : SM_Descriptions)
	{
		Target->SetVisibility(bShow, true);
	}
}

#pragma endregion