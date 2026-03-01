// Copyright by 2025-2 WAP Game 2 team

#include "Component/Interact/InteractComponent.h"
#include "UI/World/Interact/UI_Interact.h"
#include "Anomaly/Object/Neapolitan/Painting/Anomaly_Object_Painting.h"
#include "Anomaly/Object/Neapolitan/SignDrop/Anomaly_Object_SignDrop.h"
#include "Actor/Elevator/Elevator_Button.h"
#include "Component/Float/FloatComponent.h"
#include "Player/Character/EHPlayer.h"
#include <Components/StaticMeshComponent.h>
#include <NiagaraComponent.h>
#include <Materials/MaterialInstanceDynamic.h>
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
	StartBurning(1.f);
}

void UInteractComponent::Action_Elevator()
{
	Cast<AElevator_Button>(Owner)->InteractElevator();
}

#pragma endregion

#pragma region Burn
void UInteractComponent::SetupBurnTargets()
{
	if (!BurnMesh.IsValid())
	{
		BurnMesh = Owner->FindComponentByClass<UStaticMeshComponent>();
	}

	if (!BurnNiagara.IsValid())
	{
		BurnNiagara = Owner->FindComponentByClass<UNiagaraComponent>();
	}

	if (BurnMesh.IsValid() && BurnMID == nullptr)
	{
		BurnMID = BurnMesh->CreateAndSetMaterialInstanceDynamic(0);
	}
}

void UInteractComponent::StartBurning(float Duration)
{
	if (bIsBurning)
	{
		return;
	}

	SetupBurnTargets();

	GetWorld()->GetTimerManager().ClearTimer(BurnHandle);

	BurnDuration = FMath::Max(Duration, 0.01f);
	BurnCurrentTime = 0.f;
	bIsBurning = true;

	const float StartAlpha = 0.f;
	const FLinearColor BoostedEdge = EdgeColor * ColorBoost;

	BurnMID->SetScalarParameterValue(Param_Alpha, StartAlpha);
	BurnMID->SetVectorParameterValue(Param_EdgeColor, BoostedEdge);

	if (DissolveTexture)
	{
		BurnMID->SetTextureParameterValue(Param_DissolveTex, DissolveTexture);
	}

	if (UNiagaraComponent* NiagaraComp = BurnNiagara.Get())
	{
		NiagaraComp->SetVariableFloat(NiagaraVar_Alpha, StartAlpha);
		NiagaraComp->SetVariableLinearColor(NiagaraVar_EdgeColor, EdgeColor);
	}

	GetWorld()->GetTimerManager().SetTimer(BurnHandle, this, &UInteractComponent::BurnTick, 0.01f, true);
}

void UInteractComponent::BurnTick()
{
	BurnCurrentTime += GetWorld()->GetDeltaSeconds();

	float RawAlpha = FMath::Clamp(BurnCurrentTime / BurnDuration, 0.f, 1.f);

	float Alpha = RawAlpha;

	const FLinearColor BoostedEdge = EdgeColor * ColorBoost;

	BurnMID->SetScalarParameterValue(Param_Alpha, Alpha);
	BurnMID->SetVectorParameterValue(Param_EdgeColor, BoostedEdge);

	if (UNiagaraComponent* NiagaraComp = BurnNiagara.Get())
	{
		NiagaraComp->SetVariableFloat(NiagaraVar_Alpha, Alpha);
		NiagaraComp->SetVariableLinearColor(NiagaraVar_EdgeColor, EdgeColor);
	}

	if (RawAlpha >= 1.0f)
	{
		FinishBurning();
	}
}

void UInteractComponent::FinishBurning()
{

	GetWorld()->GetTimerManager().ClearTimer(BurnHandle);

	bIsBurning = false;

	UI_Interact->ShowDescription(false);

	BurnMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BurnMesh->SetGenerateOverlapEvents(false);

	Owner->SetActorEnableCollision(false);
	Owner->SetActorHiddenInGame(true);
}

#pragma endregion
