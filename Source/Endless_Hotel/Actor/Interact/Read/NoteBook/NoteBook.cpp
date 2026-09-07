// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/Read/NoteBook/NoteBook.h"
#include "UI/Base/NoteBook/UI_NoteBook.h"
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

void ANoteBook::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> Comp_Widgets = GetComponentsByTag(UWidgetComponent::StaticClass(), TEXT("Description"));
	Comp_Widgets.Sort([](const UActorComponent& First, const UActorComponent& Second)
		{
			return First.GetName() < Second.GetName();
		});

	for (int32 Index = 0; Index < Comp_Widgets.Num(); ++Index)
	{
		auto* Comp_Widget = Cast<UWidgetComponent>(Comp_Widgets[Index]);
		auto* UI_NoteBook = Cast<UUI_NoteBook>(Comp_Widget->GetUserWidgetObject());
		UI_NoteBook->ChangeDescription(Index);
	}
}

#pragma endregion

#pragma region Page

void ANoteBook::TurnOverPage(bool bLeft)
{
	FindDescription();

	UAnimInstance* AnimInstance = SKM_NoteBook->GetAnimInstance();
	UAnimMontage* TargetMontage = bLeft ? AM_LeftToRight : AM_RightToLeft;
	
	AnimInstance->Montage_Play(TargetMontage);
}

float ANoteBook::GetAnimationLength(bool bLeft)
{
	return bLeft ? AM_LeftToRight->GetPlayLength() / AM_LeftToRight->RateScale : AM_RightToLeft->GetPlayLength() / AM_RightToLeft->RateScale;
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

void ANoteBook::ShowDescription(bool bShow, uint8 Index)
{
	for (UStaticMeshComponent* Target : SM_Descriptions)
	{
		if (Target->ComponentHasTag(FName(*FString::FromInt(Index))))
		{
			Target->SetVisibility(bShow, true);
			break;
		}
	}
}

#pragma endregion