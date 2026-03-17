// Copyright by 2026-1 WAP Game 2 team

#include "Actor/HotelBlueprint/HotelBlueprint.h"
#include "UI/Controller/UI_Controller.h"
#include "Component/Interact/InteractComponent.h"
#include <Components/WidgetComponent.h>

#pragma region Base

AHotelBlueprint::AHotelBlueprint(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SM_HotelBlueprint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_HotelBlueprint"));
	SetRootComponent(SM_HotelBlueprint);

	Component_Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Component_Widget"));
	Component_Widget->SetupAttachment(RootComponent);

	Component_Interact = CreateDefaultSubobject<UInteractComponent>(TEXT("Component_Interact"));
}

#pragma endregion

#pragma region Interact

void AHotelBlueprint::Interact_Implementation()
{
	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(UI_HotelBlueprint_Class);

	Component_Interact->RestoreInteract();
}

#pragma endregion