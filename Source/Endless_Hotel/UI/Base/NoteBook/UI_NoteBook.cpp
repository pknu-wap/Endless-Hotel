// Copyright by 2026-1 WAP Game 2 team

#include "UI/Base/NoteBook/UI_NoteBook.h"
#include "Asset/Manager/EHAssetManager.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Type/Anomaly/Type_AnomalyEntry.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>

#pragma region Description

void UUI_NoteBook::ChangeDescription(uint8 Index)
{
	auto& AssetManager = UEHAssetManager::Get();
	FAnomalyEntry Entry = AssetManager.GetAnomalyData(Index);

	bool bIsClearedAnomaly = USaveManager::LoadClearedAnomalyID().Contains(Entry.ID);
	UTexture2D* TargetImage = bIsClearedAnomaly ? Entry.Picture.LoadSynchronous() : Image_Default.Get();
	FText TargetText = bIsClearedAnomaly ? Entry.Description : Text_Default;

	Image_Picture->SetBrushFromTexture(TargetImage);
	Text_Description->SetText(TargetText);
}

#pragma endregion