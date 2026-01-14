// Copyright by 2025-2 WAP Game 2 team

#include "Player/Character/EHPlayer.h"
#include "Player/Component/EHCameraComponent.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"

#pragma region Base

AEHPlayer::AEHPlayer(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Component_Camera = CreateDefaultSubobject<UEHCameraComponent>(TEXT("Component_Camera"));

	DieDelegate.AddDynamic(this, &ThisClass::DiePlayer);
}

#pragma endregion

#pragma region Death

void AEHPlayer::DiePlayer(const EDeathReason& DeathReason)
{
	UAnimMontage* DeathAnim = DeathAnims[DeathReason];

	PlayAnimMontage(DeathAnim);

	const float AnimLength = DeathAnim->GetPlayLength();

	FTimerHandle EyeHandle;
	GetWorld()->GetTimerManager().SetTimer(EyeHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			Component_Camera->StartEyeEffect(false);
		}), AnimLength, false);

	FTimerHandle DeathHandle;
	GetWorld()->GetTimerManager().SetTimer(DeathHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			auto* SubSystem = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
			SubSystem->ApplyVerdict();
		}), AnimLength + 5, false);
}

#pragma endregion