// Copyright by 2026-1 WAP Game 2 team

#include "UI/Base/NoteBook/UI_NoteBook.h"
#include "Asset/Manager/EHAssetManager.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>

#pragma region Description

void UUI_NoteBook::ChangeDescription(uint8 Index)
{
	auto& AssetManager = UEHAssetManager::Get();
	FAnomalyEntry Entry = AssetManager.GetAnomalyData(Index);

	Image_Picture->SetBrushFromTexture(Entry.Picture.LoadSynchronous());
	Text_Description->SetText(Entry.Description);
}

#pragma endregion