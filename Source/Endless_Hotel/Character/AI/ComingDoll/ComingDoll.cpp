// Copyright by 2026-1 WAP Game 2 team

#include "Character/AI/ComingDoll/ComingDoll.h"
#include <Components/AudioComponent.h>
#include <NiagaraComponent.h>

#pragma region Base

AComingDoll::AComingDoll(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AC"));
	AC->SetAutoActivate(false);
}

#pragma endregion

#pragma region Burn

void AComingDoll::SetupBurnTargets()
{
	auto* SK_Mesh = GetMesh();

	BurnDMI = SK_Mesh->CreateDynamicMaterialInstance(0);
	BurnDMI->SetScalarParameterValue(TEXT("Alpha"), 0.f);
	BurnDMI->SetVectorParameterValue(TEXT("Edge Color"), EdgeColor * ColorBoost);
	BurnDMI->SetTextureParameterValue(TEXT("Dissolve Texture"), DissolveTexture);

	SK_Mesh->SetMaterial(0, BurnDMI);
}

void AComingDoll::StartBurning()
{
	SetupBurnTargets();

	AC->Play();

	GetWorld()->GetTimerManager().SetTimer(BurnHandle, this, &ThisClass::BurnTick, 0.02f, true);
}

void AComingDoll::BurnTick()
{
	BurnCurrentTime += 0.02f;
	const float Alpha = FMath::Clamp(BurnCurrentTime / BurnDuration, 0.f, 1.f);
	BurnDMI->SetScalarParameterValue(TEXT("Alpha"), Alpha);

	if (Alpha >= 1.f)
	{
		GetWorld()->GetTimerManager().ClearTimer(BurnHandle);
		Destroy();
	}
}

#pragma endregion