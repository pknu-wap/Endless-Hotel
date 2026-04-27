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

	if (Datas.IsValidIndex(0))
	{
		Image1->SetBrushFromTexture(Datas[0]->Image_Description.LoadSynchronous());
		Text1->SetText(Datas[0]->Text_Description);
	}
	else
	{
		Image1->SetBrushFromTexture(Image_Empty);
		Text1->SetText(FText());
	}

	if (Datas.IsValidIndex(1))
	{
		Image2->SetBrushFromTexture(Datas[1]->Image_Description.LoadSynchronous());
		Text2->SetText(Datas[1]->Text_Description);
	}
	else
	{
		Image2->SetBrushFromTexture(Image_Empty);
		Text2->SetText(FText());
	}

	if (Datas.IsValidIndex(2))
	{
		Image3->SetBrushFromTexture(Datas[2]->Image_Description.LoadSynchronous());
		Text3->SetText(Datas[2]->Text_Description);
	}
	else
	{
		Image3->SetBrushFromTexture(Image_Empty);
		Text3->SetText(FText());
	}
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

#pragma endregion