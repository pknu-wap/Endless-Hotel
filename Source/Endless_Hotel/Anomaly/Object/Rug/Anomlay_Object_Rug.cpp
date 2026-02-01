#include "Anomaly/Object/Rug/Anomlay_Object_Rug.h"

#pragma region Base

AAnomlay_Object_Rug::AAnomlay_Object_Rug(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Mesh_Rug = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Rug"));
	Mesh_Rug->SetupAttachment(RootComponent);
}

#pragma endregion

#pragma region Color Change

void AAnomlay_Object_Rug::ChangeRugColor()
{
	Mesh_Rug->SetMaterial(0, ChangedMaterial);
	Mesh_Rug->SetMaterial(1, ChangedMaterial);
}

#pragma endregion