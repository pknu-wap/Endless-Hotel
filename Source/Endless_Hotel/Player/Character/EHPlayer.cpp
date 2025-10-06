// Copyright by 2025-2 WAP Game 2 team

#include "Player/Character/EHPlayer.h"
#include "Player/Component/EHCameraComponent.h"

#pragma region Base

AEHPlayer::AEHPlayer(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Component_Camera = CreateDefaultSubobject<UEHCameraComponent>(TEXT("Component_Camera"));
}

#pragma endregion