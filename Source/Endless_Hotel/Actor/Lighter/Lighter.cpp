// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Lighter/Lighter.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include <Components/WidgetComponent.h>

#pragma region Base

ALighter::ALighter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SM_Lighter = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Lighter"));
	SetRootComponent(SM_Lighter);

	Component_Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Component_Widget"));
	Component_Widget->SetupAttachment(RootComponent);

	Component_Interact = CreateDefaultSubobject<UInteractComponent>(TEXT("Component_Interact"));
}

void ALighter::BeginPlay()
{
	Super::BeginPlay();

	if (USaveManager::LoadTutorialData().bHasFlash)
	{
		Destroy();
		return;
	}
}

#pragma endregion

#pragma region Interact

void ALighter::Interact_Implementation()
{
	FSaveData_Tutorial Data = USaveManager::LoadTutorialData();
	Data.bHasFlash = true;
	USaveManager::SaveTutorialData(Data);

	Destroy();
}

#pragma endregion