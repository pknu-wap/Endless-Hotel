// Copyright by 2026-1 WAP Game 2 team

#include "UI/Base/Manual/UI_Manual_Rule.h"
#include "GameSystem/SubSystem/AnomalyPoolSubsystem.h"
#include <Components/TextBlock.h>
#include <Components/RichTextBlock.h>

#pragma region Base

void UUI_Manual_Rule::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetVisibility(ESlateVisibility::Hidden);

	Text_Index->SetText(Index);
	Text_Description->SetText(Description);

	auto* AnomalySub = GetGameInstance()->GetSubsystem<UAnomalyPoolSubsystem>();
	AnomalySub->OnAddAnomalyRule.AddDynamic(this, &ThisClass::ChangeTextState);

	if (AnomalySub->AnomalyRules.Contains(AnomalyRule))
	{
		SetVisibility(ESlateVisibility::Visible);
	}
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

#pragma endregion