// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/Hair/Anomaly_Hair.h"
#include "Anomaly/Object/EightExit/Hair/Anomaly_Object_Hair.h"
#include <GameFrameWork/Character.h>
#include <Kismet/GameplayStatics.h>

#pragma region Activity

void AAnomaly_Hair::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyID)
	{
	case EAnomalyID::Hair:
		SetupAnomalyAction<ThisClass>(&ThisClass::SpawnHair);
		ActiveTrigger();
		break;
	}
}

void AAnomaly_Hair::DisableAnomaly()
{
	if (IsValid(Hair))
	{
		Hair->Destroy();
		Hair = nullptr;
	}

	Super::DisableAnomaly();
}

#pragma endregion

#pragma region Spawn

void AAnomaly_Hair::SpawnHair()
{
	Hair = GetWorld()->SpawnActor<AAnomaly_Object_Hair>(HairClass);

	auto* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto* Mesh = Player->GetMesh();

	Hair->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("Hair"));
}

#pragma endregion