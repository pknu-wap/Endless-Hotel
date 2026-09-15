// Copyright by 2026-1 WAP Game 2 team

#include "UI/PopUp/Read/UI_PopUp_NoteBookZoomIn.h"
#include "Asset/Manager/EHAssetManager.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include <Components/Button.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>

#pragma region Base

void UUI_PopUp_NoteBookZoomIn::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_ESC->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
}

#pragma endregion

#pragma region Description

void UUI_PopUp_NoteBookZoomIn::SetDescription(uint8 Index)
{
	auto& AssetManager = UEHAssetManager::Get();
	FAnomalyEntry Entry = AssetManager.GetAnomalyData(Index);

	bool bIsClearedAnomaly = USaveManager::LoadClearedAnomalyID().Contains(Entry.ID);
	if (!bIsClearedAnomaly)
	{
		return;
	}

	UTexture2D* TargetImage = Entry.Picture.LoadSynchronous();
	FText TargetText = Entry.Description;

	Image_Picture->SetBrushFromTexture(TargetImage);
	Text_Description->SetText(TargetText);
}

#pragma endregion