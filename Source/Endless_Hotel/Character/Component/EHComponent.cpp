// Copyright by 2025-2 WAP Game 2 team

#include "Character/Component/EHComponent.h"

#pragma region Base

UEHComponent::UEHComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
}

#pragma endregion