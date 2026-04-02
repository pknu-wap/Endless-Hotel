// Copyright by 2026-1 WAP Game 2 team

#include "Actor/HotelBlueprint/HotelBlueprint.h"
#include "Component/Read/ReadComponent.h"

#pragma region Base

AHotelBlueprint::AHotelBlueprint(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Comp_Read = CreateDefaultSubobject<UReadComponent>(TEXT("Comp_Read"));

	Comp_Tutorial = CreateDefaultSubobject<UTutorialComponent>(TEXT("Comp_Tutorial"));
}

#pragma endregion

#pragma region Interact

void AHotelBlueprint::Interact_Implementation(AEHCharacter* Interacter)
{
	Super::Interact_Implementation(Interacter);

	FInteractInfo Info = Component_Interact->GetSelectedInteractInfo();

	switch (Info.InteractType)
	{
	case EInteractType::Read:
		Comp_Read->MoveCameraToTarget(Interacter, this);
		break;
	}
}

#pragma endregion