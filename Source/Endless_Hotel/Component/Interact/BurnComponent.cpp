// Copyright by 2026-1 WAP Game 2 team

#include "Component/Interact/BurnComponent.h"
#include "Anomaly/Event/Anomaly_Event.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include <Components/AudioComponent.h>
#include <NiagaraComponent.h>
#include <Materials/MaterialInstanceDynamic.h>

#pragma region Base

UBurnComponent::UBurnComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;

	Niagara_Fire = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara_Fire"));
	Niagara_Fire->SetupAttachment(this);
	Niagara_Fire->SetAutoActivate(false);

	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AC"));
	AC->SetupAttachment(Niagara_Fire);
	AC->SetAutoActivate(false);
}

#pragma endregion

#pragma region Burn

void UBurnComponent::StartBurning()
{
	Niagara_Fire->Activate();

	AC->Play();

	GetWorld()->GetTimerManager().SetTimer(BurnHandle, this, &ThisClass::BurnTick, 0.02f, true);
}

void UBurnComponent::SetupBurnTargets(UMeshComponent* Object)
{
	if (!MID_Burn.IsEmpty() && IsValid(MID_Burn[0]))
	{
		return;
	}

	BurnTarget = Object;
	MID_Burn.Empty();

	for (int32 Index = 0; Index < BurnTarget->GetNumMaterials(); ++Index)
	{
		auto* Material = BurnTarget->CreateDynamicMaterialInstance(Index);
		Material->SetScalarParameterValue(TEXT("Alpha"), 0.f);
		Material->SetVectorParameterValue(TEXT("Edge Color"), EdgeColor * ColorBoost);
		Material->SetTextureParameterValue(TEXT("Dissolve Texture"), DissolveTexture);

		MID_Burn.Add(Material);

		BurnTarget->SetMaterial(Index, MID_Burn[Index]);
	}
}

void UBurnComponent::ResetBurning()
{
	for (UMaterialInstanceDynamic* MID : MID_Burn)
	{
		MID->SetScalarParameterValue(TEXT("Alpha"), 0.f);
	}
}

void UBurnComponent::BurnTick()
{
	BurnCurrentTime += 0.02f;

	constexpr float BurnDuration = 5.f;
	const float Alpha = FMath::Clamp(BurnCurrentTime / BurnDuration, 0.f, 1.f);

	for (int32 Index = 0; Index < MID_Burn.Num(); ++Index)
	{
		MID_Burn[Index]->SetScalarParameterValue(TEXT("Alpha"), Alpha);
	}

	if (Alpha >= 1.f)
	{
		BurnTarget->SetHiddenInGame(true);
		Niagara_Fire->Deactivate();

		auto* VerdictSub = GetWorld()->GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();
		if (IsValid(VerdictSub->CurrentAnomaly) && VerdictSub->CurrentAnomaly->AnomalyID == EAnomalyID::Maze_Monster)
		{
			VerdictSub->CurrentAnomaly->InteractSolveVerdict();
		}

		GetWorld()->GetTimerManager().ClearTimer(BurnHandle);
	}
}

#pragma endregion