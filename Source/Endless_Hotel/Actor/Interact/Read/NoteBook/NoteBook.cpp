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
	UAnimInstance* AnimInstance = SKM_NoteBook->GetAnimInstance();
	UAnimMontage* TargetMontage = bLeft ? AM_LeftToRight : AM_RightToLeft;
	
	AnimInstance->Montage_Play(TargetMontage);
}

#pragma endregion