#include "Anomaly/Object/EightExit/Rug/Anomaly_Object_Rug.h"

#pragma region Color Change

void AAnomaly_Object_Rug::ChangeRugColor()
{
	Object->SetMaterial(0, ChangedMaterial);
}

#pragma endregion