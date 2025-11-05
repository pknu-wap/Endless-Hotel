// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/EightExit/FollowingPortrait/Anomaly_FollowingPortrait.h"
#include "Anomaly/Object/FollowingPortrait/Anomaly_Object_FollowingPortrait.h"

#pragma region Activity

void AAnomaly_FollowingPortrait::ActivateAnomaly_Implementation(uint8 Anomaly_ID)
{
	Super::ActivateAnomaly_Implementation(Anomaly_ID);

	switch (Anomaly_ID)
	{
	case 10:	//임시 ID 번호
		StartFollowAction();
		break;
	}
}

#pragma endregion

#pragma region Follow

void AAnomaly_FollowingPortrait::StartFollowAction()
{
	for (auto* FoundActor : LinkedObjects)
	{
		auto* Portrait = Cast<AAnomaly_Object_FollowingPortrait>(FoundActor);
		Portrait->EyeFollowing();
	}
}

#pragma endregion