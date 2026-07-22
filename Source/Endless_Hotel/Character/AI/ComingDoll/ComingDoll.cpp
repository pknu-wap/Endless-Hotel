// Copyright by 2026-1 WAP Game 2 team

#include "Character/AI/ComingDoll/ComingDoll.h"
#include "Player/Character/EHPlayer.h"
#include <Components/AudioComponent.h>
#include <Components/CapsuleComponent.h>

#pragma region Base

AComingDoll::AComingDoll(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AC"));
	AC->SetAutoActivate(false);

	DeathTrigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("DeathTrigger"));
	DeathTrigger->SetupAttachment(GetMesh());
	DeathTrigger->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnDeathTrigger);
}

#pragma endregion

#pragma region Burn

void AComingDoll::SetupBurnTargets()
{
	auto* SkeletalMesh = GetMesh();

	for (int32 Index = 0; Index < SkeletalMesh->GetNumMaterials(); ++Index)
	{
		auto* Material = SkeletalMesh->CreateDynamicMaterialInstance(Index);
		Material->SetScalarParameterValue(TEXT("Alpha"), 0.f);
		Material->SetVectorParameterValue(TEXT("Edge Color"), EdgeColor * ColorBoost);
		Material->SetTextureParameterValue(TEXT("Dissolve Texture"), DissolveTexture);

		MID_Burn.Add(Material);

		SkeletalMesh->SetMaterial(Index, MID_Burn[Index]);
	}
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

	constexpr float BurnDuration = 5.f;
	const float Alpha = FMath::Clamp(BurnCurrentTime / BurnDuration, 0.f, 1.f);

	for (int32 Index = 0; Index < MID_Burn.Num(); ++Index)
	{
		MID_Burn[Index]->SetScalarParameterValue(TEXT("Alpha"), Alpha);
	}

	if (Alpha >= 1.f)
	{
		GetWorld()->GetTimerManager().ClearTimer(BurnHandle);
		Destroy();
	}
}

#pragma endregion

#pragma region Death

void AComingDoll::OnDeathTrigger(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto* Player = Cast<AEHPlayer>(OtherActor))
	{
		Player->DieDelegate.Broadcast(EDeathReason::Doll);
		DeathTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

#pragma endregion