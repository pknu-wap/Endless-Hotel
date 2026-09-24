// Copyright by 2026-1 WAP Game 2 team

#include "UI/Base/Manual/UI_Manual_Rule.h"
#include "GameSystem/SubSystem/AnomalyPoolSubsystem.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include "GameSystem/SaveGame/SaveManager.h"
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
	if (USaveManager::LoadData_Setting().WrongCheck == EOptionValue::Off || !Rules.Contains(AnomalyRule))
	{
		Text_Underline->SetText(FText::GetEmpty());
		return;
	}

	const int32 TotalLength = Description.ToString().Len();
	const float MultiEight = USaveManager::LoadData_Setting().Language == EOptionValue::Korean ? 1.4f : 0.9f;
	const float MultiETC = USaveManager::LoadData_Setting().Language == EOptionValue::Korean ? 2.2f : 1.3f;
	const int32 TargetLength = AnomalyRule == EAnomalyRule::EightExit ? TotalLength * MultiEight : TotalLength * MultiETC;

	FString UnderLineString;
	UnderLineString.Reserve(TargetLength + TargetLength / 75 * 20);
	UnderLineString += TEXT("<UnderLine>");

	for (int32 i = 0; i < TargetLength; ++i)
	{
		if (i > 0 && i % 75 == 0)
		{
			UnderLineString += TEXT("</>");
			UnderLineString += LINE_TERMINATOR;
			UnderLineString += TEXT("<UnderLine>");
		}
		
		UnderLineString.AppendChar(TEXT(' '));
	}

	UnderLineString += TEXT("</>");

	Text_Underline->SetText(FText::FromString(UnderLineString));
}

#pragma endregion