// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "UI/UI_Base.h"
#include <CoreMinimal.h>
#include <UI_NoteBook.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UUI_NoteBook : public UUI_Base
{
	GENERATED_BODY()
	
#pragma region Description

public:
	void ChangeDescription(const uint8& StartIndex);

private:
	void HideDescription();
	void SetDescription(TArray<class UPDA_Anomaly*>& Datas, class UImage* Image, class UTextBlock* Text, uint8 Index);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image1;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image2;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image3;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text1;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text2;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text3;

	UPROPERTY(EditAnywhere, Category = "Description")
	TObjectPtr<class UTexture2D> Image_Empty;

#pragma endregion

};