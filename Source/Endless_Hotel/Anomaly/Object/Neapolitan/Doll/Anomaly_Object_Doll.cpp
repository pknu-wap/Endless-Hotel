// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/Doll/Anomaly_Object_Doll.h"
#include "Anomaly/Event/Anomaly_Event.h"
#include "Character/AI/ComingDoll/ComingDoll.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
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
	Object->SetHiddenInGame(true);
	Object->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Niagara_Fire = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara_Fire"));
	Niagara_Fire->SetupAttachment(Object);
	Niagara_Fire->SetAutoActivate(false);

	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio_Fire"));
	AC->SetupAttachment(Object);
	AC->SetAutoActivate(false);

	bSolved = false;
}

#pragma endregion

#pragma region Reset

void AAnomaly_Object_Doll::Reset()
{
	Super::Reset();

	Object->SetHiddenInGame(true);
	Object->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Niagara_Fire->Deactivate();

	for (int32 Index = 0; Index < MID_Burn.Num(); ++Index)
	{
		MID_Burn[Index]->SetScalarParameterValue(TEXT("Alpha"), 0.f);
	}

	TryBurnComingDolls();
}

#pragma endregion

#pragma region Doll

void AAnomaly_Object_Doll::ActivateDoll_Show()
{
	Object->SetHiddenInGame(false);
	Object->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
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
		StartBurning();
		TryBurnComingDolls();
		break;
	}
}

#pragma endregion

#pragma region Burn

void AAnomaly_Object_Doll::SetupBurnTargets()
{
	for (int32 Index = 0; Index < Object->GetNumMaterials(); ++Index)
	{
		auto* Material = Object->CreateDynamicMaterialInstance(Index);
		Material->SetScalarParameterValue(TEXT("Alpha"), 0.f);
		Material->SetVectorParameterValue(TEXT("Edge Color"), EdgeColor * ColorBoost);
		Material->SetTextureParameterValue(TEXT("Dissolve Texture"), DissolveTexture);

		MID_Burn.Add(Material);

		Object->SetMaterial(Index, MID_Burn[Index]);
	}
}

void AAnomaly_Object_Doll::StartBurning()
{
	SetupBurnTargets();

	Niagara_Fire->Activate();

	AC->Play();

	GetWorld()->GetTimerManager().SetTimer(BurnHandle, this, &ThisClass::BurnTick, 0.02f, true);
}

void AAnomaly_Object_Doll::BurnTick()
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
		Object->SetHiddenInGame(true);
		Niagara_Fire->Deactivate();

		auto* VerdictSub = GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();
		if (VerdictSub->CurrentAnomaly->AnomalyID == EAnomalyID::Maze_Monster)
		{
			VerdictSub->CurrentAnomaly->InteractSolveVerdict();
		}

		GetWorld()->GetTimerManager().ClearTimer(BurnHandle);
	}
}

#pragma endregion

#pragma region Coming

void AAnomaly_Object_Doll::SpawnComingDolls()
{
	UWorld* World = GetWorld();

	for (FTransform Trans : SpawnTrans)
	{
		ComingDoll.Add(World->SpawnActor<AComingDoll>(ComingDollClass, Trans));
	}
}

void AAnomaly_Object_Doll::TryBurnComingDolls()
{
	if (ComingDoll.IsEmpty())
	{
		return;
	}

	for (AComingDoll* Doll : ComingDoll)
	{
		Doll->StartBurning();
	}

	ComingDoll.Empty();
}

#pragma endregion