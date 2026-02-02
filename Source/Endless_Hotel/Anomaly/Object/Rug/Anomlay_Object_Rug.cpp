#include "Anomaly/Object/Rug/Anomlay_Object_Rug.h"

#pragma region Base

AAnomlay_Object_Rug::AAnomlay_Object_Rug(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

#pragma endregion

#pragma region Color Change

void AAnomlay_Object_Rug::ChangeRugColor()
{
	Object->SetMaterial(0, ChangedMaterial);
}

#pragma endregion