// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "UI/UI_Base.h"
#include "Type/Anomaly/Type_AnomalyEntry.h"
#include <CoreMinimal.h>
#include <UI_NoteBook.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UUI_NoteBook : public UUI_Base
{
	GENERATED_BODY()
	
#pragma region Description

public:
	void ChangeDescription(uint8 Index);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image_Picture;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text_Description;
	
#pragma endregion

};