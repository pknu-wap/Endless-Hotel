// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/HandPrint/Anomaly_Object_HandPrint.h"
#include "Components/AudioComponent.h"
#include "Components/DecalComponent.h"

#pragma region Base

bool AAnomaly_Object_HandPrint::bIsFirstHandPrint = true;

AAnomaly_Object_HandPrint::AAnomaly_Object_HandPrint(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Decal_HandPrint = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal_HandPrint"));
	RootComponent = Decal_HandPrint;
	Decal_HandPrint->SetRelativeRotation(FRotator(90, 0, 0));
	Decal_HandPrint->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	Decal_HandPrint->SetVisibility(false);

	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AC->SetupAttachment(RootComponent);
}

#pragma endregion

#pragma region Cong

void AAnomaly_Object_HandPrint::StartCongCong(float& NextCong)
{
	if (bIsFirstHandPrint)
	{
		AC->Sound = Sound_First;
		NextCong = 0.1f;
	}
	else
	{
		AC->Sound = Sound_Default;
	}

	AC->Play();

	Decal_HandPrint->SetVisibility(true);
}

#pragma endregion