// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Manual/Manual.h"
#include "Component/Read/ReadComponent.h"

#pragma region Base

AManual::AManual(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Comp_Read = CreateDefaultSubobject<UReadComponent>(TEXT("Comp_Read"));
}

#pragma endregion

#pragma region Interact

void AManual::Interact_Implementation(AEHCharacter* Interacter)
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