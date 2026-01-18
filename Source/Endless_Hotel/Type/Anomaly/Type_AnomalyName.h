// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>

UENUM(BlueprintType)
enum class EAnomalyName : uint8
{
	None				= 0		UMETA(DisplayName = "None"),
	Hair				= 1		UMETA(DisplayName = "Hair"),
	Light_Destroy		= 2		UMETA(DisplayName = "Light_Destroy"),
	Light_Blue			= 3		UMETA(DisplayName = "Light_Blue"),
	Door_Shake			= 4		UMETA(DisplayName = "Door_Shake"),
	Cry					= 5		UMETA(DisplayName = "Cry"),
	Cong				= 6		UMETA(DisplayName = "Cong"),
	Shrink				= 7		UMETA(DisplayName = "Shrink"),
	Blur				= 8		UMETA(DisplayName = "Blur"),
	Plant_Change		= 10	UMETA(DisplayName = "Plant_Change"),
	Ceil_Rotate			= 11	UMETA(DisplayName = "Ceil_Rotate"),
	Painting_Eye		= 99	UMETA(DisplayName = "Painting_Eye"),
	Painting_Blood		= 96	UMETA(DisplayName = "Painting_Blood"),
	FootStep			= 15	UMETA(DisplayName = "FootStep"),
	Painting_Blur		= 95	UMETA(DisplayName = "Painting_Blur"),
	Shelf_Book			= 9		UMETA(DisplayName = "Shelf_Book"),
	Shelf_Doll			= 98	UMETA(DisplayName = "Shelf_Doll"),
	Painting_Tilt		= 92	UMETA(DisplayName = "Painting_Tilt"),
	GhostHand			= 24	UMETA(DisplayName = "GhostHand"),
	Clock_Ringing		= 89	UMETA(DisplayName = "Clock_Ringing"),
	MusicBox_Ringing	= 90	UMETA(DisplayName = "MusicBox_Ringing"),
	Fire				= 14	UMETA(DisplayName = "Fire"),
	Door_Close			= 16	UMETA(DisplayName = "Door_Close"),
	Ceil_Blood			= 17	UMETA(DisplayName = "Ceil_Blood"),
	Float				= 88	UMETA(DisplayName = "Float")
};