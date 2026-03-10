#include "Anomaly/Object/EightExit/Rug/Anomaly_Object_Rug.h"

#pragma region Base

AAnomaly_Object_Rug::AAnomaly_Object_Rug(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

#pragma endregion

#pragma region Color Change

void AAnomaly_Object_Rug::ChangeRugColor()
{
	Object->SetMaterial(0, ChangedMaterial);
}

#pragma endregion