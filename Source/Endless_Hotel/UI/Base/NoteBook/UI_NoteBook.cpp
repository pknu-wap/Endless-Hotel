// Copyright by 2026-1 WAP Game 2 team

#include "UI/Base/NoteBook/UI_NoteBook.h"
#include "Asset/Manager/EHAssetManager.h"
#include "Asset/DataAsset/Anomaly/PDA_Anomaly.h"
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
	TArray<UPDA_Anomaly*> Datas = AssetManager.GetAnomalyDataAsset({ Index1,Index2,Index3 });

	SetDescription(Datas, Image1, Text1, Index1);
	SetDescription(Datas, Image2, Text2, Index2);
	SetDescription(Datas, Image3, Text3, Index3);
}

void UUI_NoteBook::HideDescription()
{
	Image1->SetVisibility(ESlateVisibility::Hidden);
	Image2->SetVisibility(ESlateVisibility::Hidden);
	Image3->SetVisibility(ESlateVisibility::Hidden);
	Text1->SetVisibility(ESlateVisibility::Hidden);
	Text2->SetVisibility(ESlateVisibility::Hidden);
	Text3->SetVisibility(ESlateVisibility::Hidden);

	constexpr float Duration = 0.5f;

	FTimerHandle ShowHandle;
	GetWorld()->GetTimerManager().SetTimer(ShowHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			Image1->SetVisibility(ESlateVisibility::Visible);
			Image2->SetVisibility(ESlateVisibility::Visible);
			Image3->SetVisibility(ESlateVisibility::Visible);
			Text1->SetVisibility(ESlateVisibility::Visible);
			Text2->SetVisibility(ESlateVisibility::Visible);
			Text3->SetVisibility(ESlateVisibility::Visible);
		}), Duration, false);
}

void UUI_NoteBook::SetDescription(const TArray<UPDA_Anomaly*>& Datas, UImage* Image, UTextBlock* Text, uint8 Index)
{
	if (Datas.IsValidIndex(2))
	{
		Image->SetBrushFromTexture(Datas[Index]->Image_Description.LoadSynchronous());
		Text->SetText(Datas[Index]->Text_Description);
	}
	else
	{
		Image->SetBrushFromTexture(Image_Empty);
		Text->SetText(FText());
	}
}

#pragma endregion