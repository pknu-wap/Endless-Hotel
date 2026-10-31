// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/InteractBase.h"
#include "Component/Interact/InteractComponent.h"
#include <Components/WidgetComponent.h>

#include "GameSystem/SubSystem/EHGameSystem.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"

#pragma region Base

AInteractBase::AInteractBase(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Object = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object"));
	SetRootComponent(Object);

	static ConstructorHelpers::FClassFinder<UUserWidget> UIFinder(TEXT("/Game/EndlessHotel/UI/Blueprint/Miscellaneous/InGame/WBP_Interact.WBP_Interact_C"));

	Component_Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Component_Widget"));
	Component_Widget->SetupAttachment(RootComponent);
	Component_Widget->SetWidgetSpace(EWidgetSpace::Screen);
	Component_Widget->SetWidgetClass(UIFinder.Class);

	Component_Interact = CreateDefaultSubobject<UInteractComponent>(TEXT("Component_Interact"));
}

void AInteractBase::BeginPlay()
{
	Super::BeginPlay();
	const auto* GI = GetGameInstance();
	auto* FloorSys = GI->GetSubsystem<UFloorProgressSubsystem>();
	auto* GameSys = GI->GetSubsystem<UEHGameSystem>();
	FloorSys->OnTopFloor.AddUObject(this, &ThisClass::AllowInteractOnIntro);
	GameSys->OnProgressionChanged.AddUObject(this, &ThisClass::ChangeInteractableByProgress);
}

#pragma endregion

#pragma region Interact

void AInteractBase::AllowInteractOnIntro() const
{
	Component_Interact->ActiveInteract(bAllowInteractionDuringIntro);
}

void AInteractBase::ChangeInteractableByProgress(const EGameProgression CurrentProgression) const
{
	if (CurrentProgression == EGameProgression::Tutorial)
	{
		Component_Interact->ActiveInteract(true);
	}
}

#pragma endregion