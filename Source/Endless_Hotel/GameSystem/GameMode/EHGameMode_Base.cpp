// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/GameMode/EHGameMode_Base.h"
#include "UI/Controller/UI_Controller.h"

#pragma region Base

AEHGameMode_Base::AEHGameMode_Base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEHGameMode_Base::BeginPlay()
{
	Super::BeginPlay();

	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenMapBaseWidget();
}

void AEHGameMode_Base::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

	Super::EndPlay(EndPlayReason);
}

#pragma endregion