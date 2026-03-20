// Copyright by 2025-2 WAP Game 2 team

#include "Component/Interact/InteractComponent.h"
#include "UI/World/Interact/UI_Interact.h"
#include "Interface/Interact/Interactable.h"
#include <NiagaraComponent.h>
#include <Materials/MaterialInstanceDynamic.h>
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>

#pragma region Base

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	auto* Comp_Widget = Owner->FindComponentByClass<UWidgetComponent>();
	UI_Interact = Cast<UUI_Interact>(Comp_Widget->GetUserWidgetObject());
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

#pragma region Action

void UInteractComponent::Action_Burn()
{
	SetupBurnTargets();
	StartBurning(BurnDuration);
}

#pragma endregion

#pragma region Burn

void UInteractComponent::SetupBurnTargets()
{
	if (!BurnMesh.IsValid())
	{
		TArray<UStaticMeshComponent*> Meshes;
		Owner->GetComponents<UStaticMeshComponent>(OUT Meshes);

		for (UStaticMeshComponent* M : Meshes)
		{
			if (M && M->ComponentHasTag(TEXT("BurnMesh")))
			{
				BurnMesh = M;
				break;
			}
		}


	}
	if (!BurnNiagara.IsValid())
	{
		TArray<UNiagaraComponent*> Nias;
		Owner->GetComponents<UNiagaraComponent>(OUT Nias);

		for (UNiagaraComponent* N : Nias)
		{
			if (N && N->ComponentHasTag(TEXT("BurnNiagara")))
			{
				BurnNiagara = N;
				break;
			}

		}
	}
	if (BurnMesh.IsValid())
	{
		if (!BurnMID)
		{
			BurnMID = BurnMesh->CreateAndSetMaterialInstanceDynamic(0);
		}

		if (BurnMID)
		{
			if (DissolveTexture)
			{
				BurnMID->SetTextureParameterValue(Param_DissolveTex, DissolveTexture);
			}
			BurnMID->SetVectorParameterValue(Param_EdgeColor, EdgeColor * ColorBoost);
			BurnMID->SetScalarParameterValue(Param_Alpha, 0.f);
		}
	}
}

void UInteractComponent::StartBurning(float Duration)
{
	bIsBurning = true;
	BurnCurrentTime = 0.f;
	BurnDuration = FMath::Max(0.01f, Duration);

	if (BurnNiagara.IsValid())
	{
		BurnNiagara->Activate(true);
	}

	GetWorld()->GetTimerManager().SetTimer(BurnHandle, this, &UInteractComponent::BurnTick, 0.02f, true);
}

void UInteractComponent::BurnTick()
{
	BurnCurrentTime += 0.02f;
	const float Alpha = FMath::Clamp(BurnCurrentTime / BurnDuration, 0.f, 1.f);

	if (BurnMID)
	{
		BurnMID->SetScalarParameterValue(Param_Alpha, Alpha);
	}

	if (BurnNiagara.IsValid())
	{
		BurnNiagara->SetVariableFloat(NiagaraVar_Alpha, Alpha);
		BurnNiagara->SetVariableLinearColor(NiagaraVar_EdgeColor, EdgeColor * ColorBoost);
	}

	if (Alpha >= 1.f)
	{
		FinishedBurning();
	}
}

void UInteractComponent::FinishedBurning()
{
	GetWorld()->GetTimerManager().ClearTimer(BurnHandle);
	bIsBurning = false;

	if (BurnNiagara.IsValid())
	{
		BurnNiagara->Deactivate();
	}

	Owner->SetActorHiddenInGame(true);
	Owner->SetActorEnableCollision(false);
}

#pragma endregion