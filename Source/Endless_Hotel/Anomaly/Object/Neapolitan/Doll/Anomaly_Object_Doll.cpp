// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/Neapolitan/Doll/Anomaly_Object_Doll.h"
#include <Niagara/Public/NiagaraComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/AudioComponent.h>
#include <Sound/SoundWave.h>
#include <Kismet/GameplayStatics.h>
#include <Materials/MaterialInstanceDynamic.h>

#pragma region Base

AAnomaly_Object_Doll::AAnomaly_Object_Doll(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Object->SetVisibility(false);

	Niagara_Fire = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara_Fire"));
	Niagara_Fire->SetupAttachment(Object);
	Niagara_Fire->SetAutoActivate(false);

	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio_Fire"));
	AC->SetupAttachment(Object);
	AC->SetAutoActivate(false);

	bSolved = false;
}

#pragma endregion

#pragma region Doll

void AAnomaly_Object_Doll::ActivateDoll_Show()
{
	Object->SetVisibility(true);
	Object->SetHiddenInGame(false);
}

#pragma endregion

#pragma region Interact

void AAnomaly_Object_Doll::Interact_Implementation(AEHCharacter* Interacter)
{
	Super::Interact_Implementation(Interacter);

	FInteractInfo Info = Component_Interact->GetSelectedInteractInfo();

	switch (Info.InteractType)
	{
		case EInteractType::Burn:
			SetupBurnTargets();
			StartBurning(BurnDuration);
			break;
	}
}

#pragma endregion

#pragma region Burn

void AAnomaly_Object_Doll::SetupBurnTargets()
{
	BurnMesh = Object;
	BurnNiagara = Niagara_Fire;

	if (BurnMesh.IsValid() && !BurnMID)
	{
		BurnMID = BurnMesh->CreateDynamicMaterialInstance(0);

		if(BurnMID)
		{
			BurnMesh->SetMaterial(0, BurnMID);

			BurnMID->SetScalarParameterValue(Param_Alpha, 0.f);
			BurnMID->SetVectorParameterValue(Param_EdgeColor, EdgeColor * ColorBoost);
		}

		if (DissolveTexture)
		{
			BurnMID->SetTextureParameterValue(Param_DissolveTex, DissolveTexture);
		}
	}
}

void AAnomaly_Object_Doll::StartBurning(float Duration)
{
	if (bIsBurning)
	{
		return;
	}
	
	bIsBurning = true;
	BurnCurrentTime = 0.f;
	BurnDuration = Duration;

	if (BurnNiagara.IsValid())
	{
		BurnNiagara->SetFloatParameter(NiagaraVar_Alpha, 0.f);
		BurnNiagara->SetVariableLinearColor(NiagaraVar_EdgeColor, EdgeColor * ColorBoost);
		BurnNiagara->Activate();
	}
	
	AC->Sound = Sound_Doll_Fire;
	AC->Play();

	GetWorld()->GetTimerManager().SetTimer(BurnHandle, this, &ThisClass::BurnTick, 0.02f, true);
}

void AAnomaly_Object_Doll::BurnTick()
{
	if (!bIsBurning || !BurnMID)
	{
		GetWorld()->GetTimerManager().ClearTimer(BurnHandle);
		return;
	}

	BurnCurrentTime += 0.02f;
	const float Alpha = FMath::Clamp(BurnCurrentTime / BurnDuration, 0.f, 1.f);
	BurnMID->SetScalarParameterValue(Param_Alpha, Alpha);

	if (BurnNiagara.IsValid())
	{
		BurnNiagara->SetFloatParameter(NiagaraVar_Alpha, Alpha);
	}

	if (Alpha >= 1.f)
	{
		FinishBurning();
	}
}

void AAnomaly_Object_Doll::FinishBurning()
{
	GetWorld()->GetTimerManager().ClearTimer(BurnHandle);
	bIsBurning = false;
	Destroy();
}
#pragma endregion