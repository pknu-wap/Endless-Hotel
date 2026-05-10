// Copyright by 2026-1 WAP Game 2 team

#include "UI/PopUp/Read/UI_PopUp_NoteBook.h"
#include "UI/Base/NoteBook/UI_NoteBook.h"
#include "Actor/Interact/Read/NoteBook/NoteBook.h"
#include "Asset/Manager/EHAssetManager.h"
#include <Components/Button.h>
#include <Components/WidgetComponent.h>

#pragma region Base

void UUI_PopUp_NoteBook::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Left->OnClicked.AddDynamic(this, &ThisClass::Click_ButtonLeft);
	Button_Right->OnClicked.AddDynamic(this, &ThisClass::Click_ButtonRight);
}

#pragma endregion

#pragma region Click

void UUI_PopUp_NoteBook::Click_ButtonLeft()
{
	TurnOverPage(true);
}

void UUI_PopUp_NoteBook::Click_ButtonRight()
{
	TurnOverPage(false);
}

#pragma endregion

#pragma region Widget

void UUI_PopUp_NoteBook::SettingWidget()
{
	if (IsValid(UI_NoteBook_Left.Get()) && IsValid(UI_NoteBook_Right.Get()))
	{
		return;
	}

	auto* WC_Des1 = Cast<UWidgetComponent>(TargetObject->GetComponentsByTag(UWidgetComponent::StaticClass(), FName("Description1"))[0]);
	auto* WC_Des2 = Cast<UWidgetComponent>(TargetObject->GetComponentsByTag(UWidgetComponent::StaticClass(), FName("Description2"))[0]);

	UI_NoteBook_Left = Cast<UUI_NoteBook>(WC_Des1->GetUserWidgetObject());
	UI_NoteBook_Right = Cast<UUI_NoteBook>(WC_Des2->GetUserWidgetObject());
}

#pragma endregion

#pragma region Page

void UUI_PopUp_NoteBook::TurnOverPage(bool bLeft)
{
	SettingWidget();

	int32 ChangeSize = bLeft ? -IndexChangeSize : IndexChangeSize;

	auto& AssetManager = UEHAssetManager::Get();
	if (!AssetManager.IsValidIndexAnomalyDataAsset(LeftIndex + ChangeSize))
	{
		return;
	}

	Cast<ANoteBook>(TargetObject)->TurnOverPage(bLeft);

	LeftIndex += ChangeSize;
	RightIndex += ChangeSize;

	UI_NoteBook_Left->ChangeDescription(LeftIndex);
	UI_NoteBook_Right->ChangeDescription(RightIndex);
}

#pragma endregion