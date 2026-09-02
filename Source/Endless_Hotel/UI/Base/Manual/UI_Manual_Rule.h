// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "UI/UI_Base.h"
#include "Type/Anomaly/Type_AnomalyRule.h"
#include <CoreMinimal.h>
#include <UI_Manual_Rule.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UUI_Manual_Rule : public UUI_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Data

private:
	UPROPERTY(EditAnywhere, Category = "Data")
	EAnomalyRule AnomalyRule = EAnomalyRule::None;

	UPROPERTY(EditAnywhere, Category = "Data")
	FText Index;

	UPROPERTY(EditAnywhere, Category = "Data")
	FText Description;

#pragma endregion

#pragma region Text

public:
	void SetDescriptionText(FText Text);

private:
	void ChangeTextState(EAnomalyRule Rule);
	void DrawUnderLineText(TArray<EAnomalyRule> Rules);
	FText RemoveRichTextTags(const FText& Source);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text_Index;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class URichTextBlock> Text_Description;

#pragma endregion

};