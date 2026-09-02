// Copyright by 2026-1 WAP Game 2 team

#include "UI/Base/Manual/UI_Manual_Rule.h"
#include "GameSystem/SubSystem/AnomalyPoolSubsystem.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include <Components/TextBlock.h>
#include <Components/RichTextBlock.h>

#pragma region Base

void UUI_Manual_Rule::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetVisibility(ESlateVisibility::Hidden);

	Text_Index->SetText(Index);
	Text_Description->SetText(Description);

	auto* PoolSub = GetGameInstance()->GetSubsystem<UAnomalyPoolSubsystem>();
	PoolSub->OnAddAnomalyRule.AddUObject(this, &ThisClass::ChangeTextState);
	if (PoolSub->AnomalyRules.Contains(AnomalyRule))
	{
		SetVisibility(ESlateVisibility::Visible);
	}

	auto* VerdictSub = GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();
	VerdictSub->OnOccurIncorrectRule.AddUObject(this, &ThisClass::DrawUnderLineText);
}

#pragma endregion

#pragma region Text

void UUI_Manual_Rule::SetDescriptionText(FText Text)
{
	SetVisibility(ESlateVisibility::Visible);
	Text_Index->SetVisibility(ESlateVisibility::Hidden);
	Text_Description->SetText(Text);
}

void UUI_Manual_Rule::ChangeTextState(EAnomalyRule Rule)
{
	if (AnomalyRule != Rule)
	{
		return;
	}

	SetVisibility(ESlateVisibility::Visible);
}

void UUI_Manual_Rule::DrawUnderLineText(TArray<EAnomalyRule> Rules)
{
	FText RemovedText = RemoveRichTextTags(Description);
	FText UnderLineText = FText::Format(FText::FromString(TEXT("<UnderLine>{0}</>")), RemovedText);
	FText TargetText = Rules.Contains(AnomalyRule) ? UnderLineText : Description;
	Text_Description->SetText(TargetText);
}

FText UUI_Manual_Rule::RemoveRichTextTags(const FText& Source)
{
	const FString SourceString = Source.ToString();

	FString Result;
	Result.Reserve(SourceString.Len());

	bool bInsideTag = false;

	for (const TCHAR Character : SourceString)
	{
		if (Character == TEXT('<'))
		{
			bInsideTag = true;
			continue;
		}
		else if (Character == TEXT('>'))
		{
			bInsideTag = false;
			continue;
		}

		if (!bInsideTag)
		{
			Result.AppendChar(Character);
		}
	}

	return FText::FromString(Result);
}

#pragma endregion