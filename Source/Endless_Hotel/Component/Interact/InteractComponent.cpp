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

	Comp_Tutorial = Owner->FindComponentByClass<UTutorialComponent>();
}

#pragma endregion

#pragma region Interact

void UInteractComponent::ShowInteracting(bool bIsShow)
{
	if (!CanInteract())
	{
		return;
	}

	if (!List_Interact.IsEmpty() && List_Interact.IsValidIndex(CurrentIndex) && List_Interact[CurrentIndex].bIsInteracted && HasManyInteracting())
	{
		ChangeIndex(true);
		return;
	}

	if (List_Interact.IsValidIndex(CurrentIndex))
	{
		UI_Description->SetDescription(GetDescription());
		UI_Description->ShowDescription(bIsShow, HasManyInteracting());
	}

	if (Comp_Tutorial.IsValid() && !Comp_Tutorial->bIsCheckTutorial && USaveManager::LoadData_Progression().Progression == EGameProgression::Tutorial)
	{
		return;
	}

	ShowHighlight(bIsShow);
}

void UInteractComponent::Interact(AEHCharacter* Interacter)
{
	ShowInteracting(false);

	FInteractInfo& InteractInfo = List_Interact[CurrentIndex];
	InteractInfo.bIsInteracted = true;
	bIsInteracted = true;

	if (Comp_Tutorial.IsValid() && !Comp_Tutorial->bIsCheckTutorial)
	{
		Comp_Tutorial->bIsCheckTutorial = true;
		Comp_Tutorial->HideTutorialWidget();
	}

	auto* Interface = Cast<IInteractable>(Owner);
	Interface->Interact(Interacter);
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

	if (!List_Interact.IsEmpty() && List_Interact.IsValidIndex(CurrentIndex) && List_Interact[CurrentIndex].bIsInteracted && HasManyInteracting())
	{
		ChangeIndex(true);
		return;
	}
}

#pragma endregion

#pragma region Hightight

void UInteractComponent::ShowHighlight(bool bActive)
{
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