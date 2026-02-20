// Copyright by 2025-2 WAP Game 2 team

#include "Component/Interact/InteractComponent.h"
#include "UI/World/Interact/UI_Interact.h"
#include "Anomaly/Object/Neapolitan/Painting/Anomaly_Object_Painting.h"
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

bool UInteractComponent::CanInteract() 
{
	if (auto* FloatComp = Owner->FindComponentByClass<UAnomaly_Component_Float>())
	{
		if (FloatComp->bIsFloating)
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

#pragma region Action

void UInteractComponent::Action_Restore()
{
	StartRestoring(2.5);
}

void UInteractComponent::Action_Rotate()
{
	Cast<AAnomaly_Object_Painting>(Owner)->InteractRotate();
}

void UInteractComponent::Action_TurnOff()
{
	// 시끄러운 소리 물체 관련 상호작용의 공통 코드 모음
	// 나머지 필요한 기능들은 AdditionalAction에 집어넣기
	Cast<AAnomaly_Object_Neapolitan>(Owner)->bSolved = true;
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

#pragma region Restore

void UInteractComponent::SaveOriginalTransform()
{
	OriginalTransform = Owner->GetActorTransform();
}

void UInteractComponent::StartRestoring(float Duration)
{
	GetWorld()->GetTimerManager().ClearTimer(RestoreHandle);

	RestoreDuration = FMath::Max(Duration, 0.01f);
	RestoreCurrentTime = 0.f;

	GetWorld()->GetTimerManager().SetTimer(RestoreHandle, this, &UInteractComponent::RestoreTick, 0.01f, true);
}

void UInteractComponent::RestoreTick()
{
	RestoreCurrentTime += GetWorld()->GetDeltaSeconds();
	float RawAlpha = FMath::Clamp(RestoreCurrentTime / RestoreDuration, 0.f, 1.f);
	float Alpha = FMath::InterpEaseInOut(0.f, 1.f, RawAlpha, 2.f);

	FTransform CurrentTransform = Owner->GetActorTransform();
	FTransform NewTransform;
	NewTransform.Blend(CurrentTransform, OriginalTransform, Alpha);
	Owner->SetActorTransform(NewTransform);

	if (RawAlpha >= 1.0f)
	{
		FinishRestoring();
	}
}

void UInteractComponent::FinishRestoring()
{
	GetWorld()->GetTimerManager().ClearTimer(RestoreHandle);

	Owner->SetActorTransform(OriginalTransform);

	if (UPrimitiveComponent* RootPrim = Cast<UPrimitiveComponent>(Owner->GetRootComponent()))
	{
		RootPrim->SetSimulatePhysics(false);
	}

	if (OnRestored.IsBound())
	{
		OnRestored.Broadcast(Owner.Get());
	}
}

#pragma endregion