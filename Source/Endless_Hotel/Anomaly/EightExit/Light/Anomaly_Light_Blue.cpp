// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Light/Anomaly_Light_Blue.h"
#include "Anomaly/Object/Light/Anomaly_Object_Light.h"

#pragma region Base

AAnomaly_Light_Blue::AAnomaly_Light_Blue(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	LightAction = ([](AAnomaly_Object_Light* Light)
		{
			Light->ChangeLightColor();
		});
}

#pragma endregion