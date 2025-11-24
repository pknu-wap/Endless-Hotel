// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Default/Compendium/UI_PopUp_Compendium.h"
#include "UI/Controller/UI_Controller.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#pragma region Base

void UUI_PopUp_Compendium::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Previous->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Previous);
	Button_Next->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Next);
	Button_Close->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
}

void UUI_PopUp_Compendium::NativeConstruct()
{
	Super::NativeConstruct();

	CheckCompendiumData();
}

#pragma endregion

#pragma region Data

void UUI_PopUp_Compendium::CheckCompendiumData()
{
	TArray<FCompendiumData> Data = USaveManager::LoadCompendiumData();

	if (Data.IsEmpty())
	{
		return;
	}

	ActiveCompendiumData(Data, Box_Left, Page_Left);
	ActiveCompendiumData(Data, Box_Right, Page_Right);
}

void UUI_PopUp_Compendium::ActiveCompendiumData(TArray<FCompendiumData> Data, UVerticalBox* Box, int32 Page)
{
	for (int32 Index = 1; Index <= 3; Index++)
	{
		FCompendiumData Target;
		Target.Index = (Page - 1) * 3 + Index;

		if (!Data[Data.Find(Target)].bIsChecked)
		{
			continue;
		}

		UHorizontalBox* ChildBox = Cast<UHorizontalBox>(Box->GetChildAt(Index));

		for (auto Widget : ChildBox->GetAllChildren())
		{
			if (UImage* Image = Cast<UImage>(Widget))
			{
				Image->SetVisibility(ESlateVisibility::Visible);
			}
			else if (UTextBlock* Text = Cast<UTextBlock>(Widget))
			{
				Text->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}

#pragma endregion

#pragma region Button

void UUI_PopUp_Compendium::ButtonClick_Previous()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenPopUpWidget(UI_Previous);
}

void UUI_PopUp_Compendium::ButtonClick_Next()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenPopUpWidget(UI_Next);
}

#pragma endregion