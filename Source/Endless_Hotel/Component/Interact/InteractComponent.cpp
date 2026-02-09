// Copyright by 2025-2 WAP Game 2 team

#include "Component/Interact/InteractComponent.h"
#include "UI/World/Interact/UI_Interact.h"
#include "Anomaly/Object/Anomaly_Object_Neapolitan.h"
#include "Elevator/Elevator_Button.h"
#include <Components/WidgetComponent.h>

#pragma region Interact

void UInteractComponent::ShowDescriptionWidget(bool bIsShow)
{
	if (!CanInteract())
	{
		return;
	}

	auto* Comp_Widget = Owner->FindComponentByClass<UWidgetComponent>();
	auto* UI_Interact = Cast<UUI_Interact>(Comp_Widget->GetUserWidgetObject());

	UI_Interact->ShowDescription(bIsShow);
	UI_Interact->SetDescription(GetDescription());
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
	InteractInfo.bIsInteracted = !InteractInfo.bIsInteracted;

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

#pragma region Action

void UInteractComponent::Action_Restore()
{
	// 복구시키기 (담당: 미스 조)
}

void UInteractComponent::Action_Rotate()
{
	// 그림 회전 (담당: 경원 김)
}

void UInteractComponent::Action_TurnOff()
{
	// 시끄러운 소리 물체 관련 상호작용의 공통 코드 모음
	// 나머지 필요한 기능들은 AdditionalAction에 집어넣기
	Cast<AAnomaly_Object_Neapolitan>(this)->bSolved = true;
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