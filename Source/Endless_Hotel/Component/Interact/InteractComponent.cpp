// Copyright by 2025-2 WAP Game 2 team

#include "Component/Interact/InteractComponent.h"
#include "UI/Interact/UI_Interact.h"
#include "Interface/Interact/Interactable.h"
#include <Components/WidgetComponent.h>

#pragma region Base

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	auto* Comp_Widget = Owner->FindComponentByClass<UWidgetComponent>();
	UI_Interact = Cast<UUI_Interact>(Comp_Widget->GetUserWidgetObject());
	UI_Interact->ShowDescription(false);
}

#pragma endregion

#pragma region Interact

void UInteractComponent::ShowInteracting(bool bIsShow)
{
	ShowDescriptionWidget(bIsShow);
	ShowInteractingHighlight(bIsShow);
}

void UInteractComponent::ShowDescriptionWidget(bool bIsShow)
{
	if (!List_Interact.IsValidIndex(CurrentIndex))
	{
		return;
	}

	if (!CanInteract())
	{
		return;
	}

	if (UI_Interact.IsValid())
	{
		UI_Interact->SetDescription(GetDescription());
		UI_Interact->ShowDescription(bIsShow);
	}
}

void UInteractComponent::ChangeIndex(bool bUp)
{
	if (bUp)
	{
		CurrentIndex++;
		if (CurrentIndex >= List_Interact.Num())
		{
			CurrentIndex = 0;
		}
		return;
	}
	
	CurrentIndex--;
	if (CurrentIndex < 0)
	{
		CurrentIndex = List_Interact.Num() - 1;
	}
}

void UInteractComponent::Interact(AEHCharacter* Interacter)
{
	ShowInteracting(false);

	FInteractInfo& InteractInfo = List_Interact[CurrentIndex];
	InteractInfo.bIsInteracted = true;
	bIsInteracted = true;

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

#pragma endregion

#pragma region Hightight

void UInteractComponent::ShowInteractingHighlight(bool bActive)
{
	if (!CanInteract())
	{
		return;
	}

	TArray<UMeshComponent*> Comps;
	Owner->GetComponents<UMeshComponent>(OUT Comps);

	for (auto Target : Comps)
	{
		if (Target->ComponentHasTag(HighlightTag))
		{
			Target->SetRenderCustomDepth(bActive);
			Target->MarkRenderStateDirty();
		}
	}
}

#pragma endregion