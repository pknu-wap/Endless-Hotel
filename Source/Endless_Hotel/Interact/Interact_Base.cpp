﻿// Copyright by 2025-2 WAP Game 2 team

#include "Interact/Interact_Base.h"

#pragma region Base

AInteract_Base::AInteract_Base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

#pragma endregion