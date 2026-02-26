// Copyright by 2025-2 WAP Game 2 team

#include "Component/Interact/InteractComponent.h"
#include "UI/World/Interact/UI_Interact.h"
#include "Anomaly/Object/Neapolitan/Painting/Anomaly_Object_Painting.h"
#include "Anomaly/Object/Neapolitan/SignDrop/Anomaly_Object_SignDrop.h"
#include "Actor/Elevator/Elevator_Button.h"
#include "Component/Float/FloatComponent.h"
#include "Player/Character/EHPlayer.h"
#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>

#pragma region Base

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Comp_Widget = Owner->FindComponentByClass<UWidgetComponent>();
	UI_Interact = Cast<UUI_Interact>(Comp_Widget->GetUserWidgetObject());
}

#pragma endregion

#pragma region Interact

void UInteractComponent::ShowInteracting(bool bIsShow)
{
	ShowDescriptionWidget(bIsShow);
	ShowInteractingHighlight(bIsShow);
}

bool UInteractComponent::CanInteract()
{
	if (auto* FloatComp = Owner->FindComponentByClass<UFloatComponent>())
	{
		if (!FloatComp->bIsFloatStarted || FloatComp->bIsFloating)
		{
			return false;
		}
	}

	return !List_Interact.IsEmpty() && !bIsInteracted;
}

void UInteractComponent::ShowDescriptionWidget(bool bIsShow)
{
	if (!List_Interact.IsValidIndex(CurrentIndex))
	{
		return;
	}

	if (!CanInteract())
	{
		bIsShow = false;
	}

	if (UI_Interact.IsValid())
	{
		UI_Interact->ShowDescription(bIsShow);
		UI_Interact->SetDescription(GetDescription());
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

void UInteractComponent::Interact()
{
	FInteractInfo& InteractInfo = List_Interact[CurrentIndex];
	InteractInfo.bIsInteracted = true;
	bIsInteracted = true;

	switch (InteractInfo.InteractType)
	{
	case EInteractType::Restore:
		Action_Restore();
		break;

	case EInteractType::Rotate:
		Action_Rotate();
		break;

	case EInteractType::TurnOff:
		Action_TurnOff();
		break;

	case EInteractType::Burn:
		Action_Burn();
		break;

	case EInteractType::Elevator:
		Action_Elevator();
		break;
	}

	if (AdditionalAction)
	{
		AdditionalAction();
	}
}

#pragma endregion

#pragma region Hightight

void UInteractComponent::ShowInteractingHighlight(bool bActive)
{
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

#pragma region Action

void UInteractComponent::Action_Restore()
{
	if (FloatActorClass)
	{
		if (UFloatComponent* FloatComp = Owner->FindComponentByClass<UFloatComponent>())
		{
			FloatComp->StartRestoring(2.5f);
		}
	}

	if (SignActorClass)
	{
		if (AAnomaly_Object_SignDrop* SignActor = Cast<AAnomaly_Object_SignDrop>(Owner))
		{
			SignActor->StartRestoring(2.5f);
		}
	}
}

void UInteractComponent::Action_Rotate()
{
	Cast<AAnomaly_Object_Painting>(Owner)->InteractRotate();
}

void UInteractComponent::Action_TurnOff()
{
	
}

void UInteractComponent::Action_Burn()
{
	// 불 태우기 (담당: 서은 심)
}

void UInteractComponent::Action_Elevator()
{
	Cast<AElevator_Button>(Owner)->InteractElevator();
}

#pragma endregion
