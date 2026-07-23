// Copyright by 2026-1 WAP Game 2 team

#include "UI/Base/Manual/UI_Manual_Rule.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include <Components/TextBlock.h>
#include <Components/RichTextBlock.h>

#pragma region Base

void UUI_Manual_Rule::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetVisibility(ESlateVisibility::Hidden);

	Text_Index->SetText(Index);
	Text_Description->SetText(Description);

	auto* GameSystem = GetGameInstance()->GetSubsystem<UGameSystem>();
	GameSystem->OnAddAnomalyRule.AddDynamic(this, &ThisClass::ChangeTextState);

	if (GameSystem->AnomalyRules.Contains(AnomalyRule))
	{
		SetVisibility(ESlateVisibility::Visible);
	}
}

#pragma endregion

#pragma region Text

void UUI_Manual_Rule::ChangeTextState(EAnomalyRule Rule)
{
	if (AnomalyRule != Rule)
	{
		return;
	}

	SetVisibility(ESlateVisibility::Visible);
}

#pragma endregion