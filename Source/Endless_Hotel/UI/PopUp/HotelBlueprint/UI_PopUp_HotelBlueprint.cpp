	// Copyright by 2026-1 WAP Game 2 team

#include "UI/PopUp/HotelBlueprint/UI_PopUp_HotelBlueprint.h"
#include "Actor/HotelBlueprint/HotelBlueprint.h"


#pragma region Input

void UUI_PopUp_HotelBlueprint::Input_ESC()
{
	HotelBlueprint->RestoreCamera();

	Super::Input_ESC();
}

void UUI_PopUp_HotelBlueprint::SetHotelBlueprint(AHotelBlueprint* HB)
{
	HotelBlueprint = HB;
}

#pragma endregion