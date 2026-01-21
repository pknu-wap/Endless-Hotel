// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/Disappear/Anomaly_Object_Disappear.h"
#include <Components/StaticMeshComponent.h>

#pragma region Base

AAnomaly_Object_Disappear::AAnomaly_Object_Disappear(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SM_Object = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Object"));
	SM_Object->SetupAttachment(RootComponent);
	SM_Object->SetVisibility(bVisible);
}

#pragma endregion

#pragma region Activity
void AAnomaly_Object_Disappear::StartDisappear()
{
	bVisible = false;
	SM_Object->SetVisibility(bVisible);
}
#pragma endregion