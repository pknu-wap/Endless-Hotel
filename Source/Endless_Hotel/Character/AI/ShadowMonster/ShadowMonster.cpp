// Copyright by 2026-1 WAP Game 2 team

#include "Character/AI/ShadowMonster/ShadowMonster.h"
#include "Character/AI/ShadowMonster/ShadowMonsterAnimInstance.h"
#include <Components/SkeletalMeshComponent.h>

#pragma region Appear

void AShadowMonster::StartAppear()
{
	if (bIsAppearing)
	{
		return;
	}
	
	UShadowMonsterAnimInstance* Anim = GetShadowAnim();
	if (!IsValid(Anim))
	{
		return;
	}
	
	bIsAppearing = true;
	SetAnimRootMotionTranslationScale(AppearRootMotionScale);
	SetActorHiddenInGame(false);
	Anim->bMonsterAppear = true;
}

void AShadowMonster::SetAppearPlaying(bool bPlaying)
{
	if (bPlaying)
	{
		StartAppear();
	}

	UShadowMonsterAnimInstance* Anim = GetShadowAnim();
	if (!IsValid(Anim))
	{
		return;
	}
	Anim->AppearPlayRate = bPlaying ? 1.f : 0.f;
}

UShadowMonsterAnimInstance* AShadowMonster::GetShadowAnim() const
{
	const USkeletalMeshComponent* AnimMesh = GetMesh();

	if (!IsValid(AnimMesh))
	{
		return nullptr;
	}
	return Cast<UShadowMonsterAnimInstance>(AnimMesh->GetAnimInstance());
}

#pragma endregion