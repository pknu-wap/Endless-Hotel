// Copyright by 2026-1 WAP Game 2 team

#include "Character/AI/ShadowMonster/ShadowMonsterController.h"
#include "ShadowMonster.h"
#include "Anomaly/Object/Neapolitan/Painting/Anomaly_Object_Painting.h"

#pragma region Appear

void AShadowMonsterController::StartBind(AAnomaly_Object_Painting* OwnerPainting)
{
	OwnerPainting->OnMonsterAppear.AddUObject(this, &ThisClass::HandleMonsterAppear);
}

void AShadowMonsterController::HandleMonsterAppear(const bool bAppear)
{
	AShadowMonster* Monster = Cast<AShadowMonster>(GetPawn());
	if (bAppear)
	{
		Monster->StartAppear();
	}
	else
	{
		StopMovement();
		Monster->ResetToTransform(InitialTransform);
	}
}

#pragma endregion