// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/InteractBase.h"
#include "Component/Interact/InteractComponent.h"
#include <Components/WidgetComponent.h>

#pragma region Base

AInteractBase::AInteractBase(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Object = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object"));
	SetRootComponent(Object);

	static ConstructorHelpers::FClassFinder<UUserWidget> UIFinder(TEXT("/Game/EndlessHotel/UI/Blueprint/InGame/WBP_Interact.WBP_Interact_C"));

	Component_Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Component_Widget"));
	Component_Widget->SetupAttachment(RootComponent);
	Component_Widget->SetWidgetSpace(EWidgetSpace::Screen);
	Component_Widget->SetWidgetClass(UIFinder.Class);

	Component_Interact = CreateDefaultSubobject<UInteractComponent>(TEXT("Component_Interact"));
}

#pragma endregion