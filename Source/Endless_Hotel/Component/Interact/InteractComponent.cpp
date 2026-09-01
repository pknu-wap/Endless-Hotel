// Copyright by 2025-2 WAP Game 2 team

#include "Component/Interact/InteractComponent.h"
#include "Component/Tutorial/TutorialComponent.h"
#include "UI/Base/Interact/UI_Interact.h"
#include "Interface/Interact/Interactable.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include <Components/WidgetComponent.h>

#pragma region Base

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	auto* Comp_Widget = Owner->FindComponentByClass<UWidgetComponent>();
	UI_Description = Cast<UUI_Interact>(Comp_Widget->GetUserWidgetObject());
	UI_Description->ShowDescription(false, false);
}

#pragma endregion

#pragma region Interact

void UInteractComponent::ShowInteracting(bool bIsShow)
{
	if (List_Interact.IsValidIndex(CurrentIndex) && CanInteract() && UI_Description.IsValid())
	{
		UI_Description->SetDescription(GetDescription());
		UI_Description->ShowDescription(bIsShow, HasManyInteracting());
	}

	ShowHighlight(bIsShow);
}

void UInteractComponent::Interact(AEHCharacter* Interacter)
{
	ShowInteracting(false);

	FInteractInfo& InteractInfo = List_Interact[CurrentIndex];
	InteractInfo.bIsInteracted = true;
	bIsInteracted = true;

	auto* Comp_Tutorial = Owner->FindComponentByClass<UTutorialComponent>();
	if (IsValid(Comp_Tutorial))
	{
		Comp_Tutorial->HideTutorialWidget();
	}

	IInteractable::Execute_Interact(Owner.Get(), Interacter);
}

FInteractInfo UInteractComponent::GetSelectedInteractInfo()
{
	if (List_Interact.IsEmpty())
	{
		return FInteractInfo();
	}

	return List_Interact[CurrentIndex];
}

void UInteractComponent::ActiveInteract(bool bActive)
{
	for (auto& Info : List_Interact)
	{
		Info.bIsInteracted = bActive;
	}
}

#pragma endregion

#pragma region Index

void UInteractComponent::TryChangeIndex(bool bUp)
{
	if (!HasManyInteracting() || bChangingIndex)
	{
		return;
	}

	UI_Description->PlayChangeAnimation(bUp);

	bChangingIndex = true;

	constexpr float ChangeDuration = 0.3f;

	FTimerHandle TextHandle;
	GetWorld()->GetTimerManager().SetTimer(TextHandle, FTimerDelegate::CreateUObject(this, &ThisClass::ChangeIndex, bUp), ChangeDuration, false);
}

void UInteractComponent::ChangeIndex(bool bUp)
{
	bChangingIndex = false;

	bUp ? ++CurrentIndex : --CurrentIndex;

	if (CurrentIndex >= List_Interact.Num())
	{
		CurrentIndex = 0;
	}
	else if (CurrentIndex < 0)
	{
		CurrentIndex = List_Interact.Num() - 1;
	}

	if (List_Interact[CurrentIndex].bIsInteracted)
	{
		ChangeIndex(bUp);
	}
}

#pragma endregion

#pragma region Hightight

void UInteractComponent::ShowHighlight(bool bActive)
{
	if (!CanInteract())
	{
		return;
	}

	TArray<UMeshComponent*> Comps;
	Owner->GetComponents<UMeshComponent>(OUT Comps);

	for (auto Target : Comps)
	{
		if (Target->ComponentHasTag(HIGHLIGHT_TAG))
		{
			Target->SetRenderCustomDepth(bActive);
			Target->MarkRenderStateDirty();
		}
	}
}

#pragma endregion