// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/Neapolitan/Painting/Anomaly_Painting.h"
#include "Anomaly/Object/Neapolitan/Painting/Anomaly_Object_Painting.h"
#include "Character/AI/ShadowMonster/ShadowMonster.h"
#include "Character/AI/ShadowMonster/ShadowMonsterController.h"

#pragma region Activity

void AAnomaly_Painting::SetAnomalyState()
{
	Super::SetAnomalyState();
	const FAnomalyActionInfo SolveInfo = GetRuleActionInfo();

	switch (AnomalyID)
	{
	case EAnomalyID::Painting_Eye:
		SetupAnomalyAction<AAnomaly_Object_Painting>(&AAnomaly_Object_Painting::EyeFollowing, SolveInfo);
		ScheduleAnomaly();
		break;
	case EAnomalyID::Painting_Blood:
		SetupAnomalyAction<AAnomaly_Object_Painting>(&AAnomaly_Object_Painting::BloodDropping, SolveInfo);
		ScheduleAnomaly();
		break;
	case EAnomalyID::Painting_Blur:
		SetupAnomalyAction<AAnomaly_Object_Painting>(&AAnomaly_Object_Painting::BlurPaint, SolveInfo);
		ScheduleAnomaly();
		break;
	case EAnomalyID::Painting_Tilt:
		SetupAnomalyAction<AAnomaly_Object_Painting>(&AAnomaly_Object_Painting::FrameTilt, SolveInfo);
		ScheduleAnomaly(10.0f);
		break;
	case EAnomalyID::Painting_Picture:
		SetupAnomalyAction<AAnomaly_Object_Painting>(&AAnomaly_Object_Painting::ChangePicture, SolveInfo);
		ScheduleAnomaly();
		break;
	case EAnomalyID::Painting_Watch:
		SetupAnomalyAction<AAnomaly_Object_Painting>(&AAnomaly_Object_Painting::SpawnMonsterWatchingPainting);
		SetupAnomalyAction<ThisClass>(&ThisClass::SpawnShadowMonster);
		ScheduleAnomaly();
		break;
	}
}

#pragma endregion

#pragma region Watch

void AAnomaly_Painting::SpawnShadowMonster()
{
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ShadowMonster = GetWorld()->SpawnActor<AShadowMonster>(ShadowMonsterClass, SpawnTransform, Params);
	ShadowMonster->SetActorHiddenInGame(true);
	DispatchToObject<AAnomaly_Object_Painting>(&AAnomaly_Object_Painting::OnShadowMonsterSpawnedHandler, Cast<AShadowMonsterController>(ShadowMonster->GetController()));
}

#pragma endregion