// Copyright by 2026-1 WAP Game 2 team

#include "UI/PopUp/Read/UI_PopUp_Read.h"
#include "Component/Read/ReadComponent.h"

#pragma region Input

void UUI_PopUp_Read::Input_ESC()
{
	auto* Comp_Read = TargetObject->FindComponentByClass<UReadComponent>();
	Comp_Read->RestoreCamera();

	Super::Input_ESC();
}

#pragma endregion