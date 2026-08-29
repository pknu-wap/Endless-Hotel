// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Object/EightExit/CrawlChild/Anomaly_Object_PillBottle.h"

#pragma region Base

AAnomaly_Object_PillBottle::AAnomaly_Object_PillBottle(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	CapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CapMesh"));
	CapMesh->SetupAttachment(RootComponent);
}

#pragma endregion