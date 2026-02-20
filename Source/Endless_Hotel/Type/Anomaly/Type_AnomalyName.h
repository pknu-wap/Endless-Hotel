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
	Shelf_Book			= 9		UMETA(DisplayName = "Shelf_Book"),
	Plant_Change		= 10	UMETA(DisplayName = "Plant_Change"),
	Ceil_Rotate			= 11	UMETA(DisplayName = "Ceil_Rotate"),
	Choose              = 12	UMETA(DisplayName = "Choose"),
	Bug					= 13	UMETA(DisplayName = "Bug"),
	Fire				= 14	UMETA(DisplayName = "Fire"),
	FootStep			= 15	UMETA(DisplayName = "FootStep"),
	Door_Close			= 16	UMETA(DisplayName = "Door_Close"),
	Ceil_Blood			= 17	UMETA(DisplayName = "Ceil_Blood"),
	Disappear			= 18	UMETA(DisplayName = "Disappear"),
	FireCorridor		= 22	UMETA(DisplayName = "FireCorridor"),
	Rug_Color 		    = 23	UMETA(DisplayName = "Rug_Color"),
	GhostHand			= 24	UMETA(DisplayName = "GhostHand"),
	Ghost               = 28	UMETA(DisplayName = "Ghost"),
	Twin				= 85	UMETA(DisplayName = "Twin"),
	SignDrop			= 86	UMETA(DisplayName = "SignDrop"),
	Float				= 88	UMETA(DisplayName = "Float"),
	Clock_Ringing		= 89	UMETA(DisplayName = "Clock_Ringing"),
	MusicBox_Ringing	= 90	UMETA(DisplayName = "MusicBox_Ringing"),
	Painting_Tilt		= 92	UMETA(DisplayName = "Painting_Tilt"),
	Painting_Blur		= 95	UMETA(DisplayName = "Painting_Blur"),
	Painting_Blood		= 96	UMETA(DisplayName = "Painting_Blood"),
	Shelf_Doll			= 98	UMETA(DisplayName = "Shelf_Doll"),
	Painting_Eye		= 99	UMETA(DisplayName = "Painting_Eye")
};