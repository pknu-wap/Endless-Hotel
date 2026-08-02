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
	if (!UI_NoteBooks.IsEmpty())
	{
		return;
	}

	TArray<UActorComponent*> Array = TargetObject->GetComponentsByTag(UWidgetComponent::StaticClass(), TEXT("Description"));

	Array.Sort([](const UActorComponent& First, const UActorComponent& Second)
		{
			return First.GetName() < Second.GetName();
		});

	for (auto* Target : Array)
	{
		auto* Comp_Widget = Cast<UWidgetComponent>(Target);
		auto* UI_NoteBook = Cast<UUI_NoteBook>(Comp_Widget->GetUserWidgetObject());
		UI_NoteBooks.Add(UI_NoteBook);
	}
}

#pragma endregion

#pragma region Page

void UUI_PopUp_NoteBook::TurnOverPage(bool bLeft)
{
	SettingWidget();

	int32 ChangeSize = bLeft ? -IndexChangeSize : IndexChangeSize;

	auto& AssetManager = UEHAssetManager::Get();
	if (!AssetManager.IsValidIndexAnomalyData(PageStartIndex + ChangeSize))
	{
		return;
	}

	PageStartIndex += ChangeSize;

	auto* NoteBook = Cast<ANoteBook>(TargetObject);
	NoteBook->TurnOverPage(bLeft);

	for (int32 Index = 0; Index < UI_NoteBooks.Num(); ++Index)
	{
		UUI_NoteBook* UI_NoteBook = UI_NoteBooks[Index].Get();
		UI_NoteBook->ChangeDescription(PageStartIndex + Index);
		UI_NoteBook->SetVisibility(ESlateVisibility::Hidden);

		NoteBook->ShowDescription(false, Index);
	}

	const float MontageLength = NoteBook->GetAnimationLength(bLeft);
	GetWorld()->GetTimerManager().SetTimer(TextHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			for (int32 Index = 0; Index < UI_NoteBooks.Num(); ++Index)
			{
				UUI_NoteBook* UI_NoteBook = UI_NoteBooks[Index].Get();
				UI_NoteBook->SetVisibility(ESlateVisibility::Visible);

				auto& AssetManager = UEHAssetManager::Get();
				if (AssetManager.IsValidIndexAnomalyData(PageStartIndex + Index))
				{
					auto* NoteBook = Cast<ANoteBook>(TargetObject);
					NoteBook->ShowDescription(true, Index);
				}
			}
		}), MontageLength, false);
}

#pragma endregion