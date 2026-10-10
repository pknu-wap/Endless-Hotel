// Copyright by 2026-1 WAP Game 2 team

#include "Character/AI/ShadowMonster/ShadowMonster.h"
#include "ShadowMonsterAnimInstance.h"

#pragma region Appear

void AShadowMonster::StartAppear()
{
	if (bIsAppearing)
	{
		return;
	}
	bIsAppearing = true;
	SetAnimRootMotionTranslationScale(AppearRootMotionScale);
	SetActorHiddenInGame(false);
	if (auto* Anim = GetShadowAnim())
	{
		Anim->bMonsterAppear = true;
	}
}

UShadowMonsterAnimInstance* AShadowMonster::GetShadowAnim() const
{
	return Cast<UShadowMonsterAnimInstance>(GetMesh()->GetAnimInstance());
}

#pragma endregion