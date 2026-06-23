// Copyright by 2026-1 WAP Game 2 team

#include "UI/Base/NoteBook/UI_NoteBook.h"
#include "Asset/Manager/EHAssetManager.h"
#include "Asset/DataAsset/Anomaly/PDA_Anomaly.h"
#include "Type/Anomaly/Type_AnomalyEntry.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>

#pragma region Description

void UUI_NoteBook::ChangeDescription(const uint8& StartIndex)
{
	HideDescription();

	uint8 Index1 = StartIndex;
	uint8 Index2 = StartIndex + 1;
	uint8 Index3 = StartIndex + 2;

	auto& AssetManager = UEHAssetManager::Get();
	TArray<UPDA_Anomaly*> PDAs = AssetManager.GetAnomalyDataAsset({ Index1,Index2,Index3 });

	TArray<FAnomalyEntry> Datas;
	for (UPDA_Anomaly* PDA : PDAs)
	{
		if (!PDA) continue;
		Datas.Append(PDA->Entries);
	}

	SetDescription(Datas, Image1, Text1, 0);
	SetDescription(Datas, Image2, Text2, 1);
	SetDescription(Datas, Image3, Text3, 2);
}

void UUI_NoteBook::HideDescription()
{
	Image1->SetVisibility(ESlateVisibility::Collapsed);
	Image2->SetVisibility(ESlateVisibility::Collapsed);
	Image3->SetVisibility(ESlateVisibility::Collapsed);
	Text1->SetVisibility(ESlateVisibility::Collapsed);
	Text2->SetVisibility(ESlateVisibility::Collapsed);
	Text3->SetVisibility(ESlateVisibility::Collapsed);

	constexpr float Duration = 0.5f;

	FTimerHandle ShowHandle;
	GetWorld()->GetTimerManager().SetTimer(ShowHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			Image1->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			Image2->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			Image3->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			Text1->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			Text2->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			Text3->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}), Duration, false);
}

void UUI_NoteBook::SetDescription(TArray<FAnomalyEntry>& Datas, UImage* Image, UTextBlock* Text, uint8 Index)
{
	if (Datas.IsValidIndex(Index))
	{
		Image->SetBrushFromTexture(Datas[Index].Image_Description.LoadSynchronous());
		Text->SetText(Datas[Index].Text_Description);
	}
	else
	{
		Image->SetBrushFromTexture(Image_Empty);
		Text->SetText(FText());
	}
}

#pragma endregion