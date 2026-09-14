// Copyright by 2026-1 WAP Game 2 team

#include "UI/PopUp/Read/UI_PopUp_NoteBook.h"
#include "UI/Base/NoteBook/UI_NoteBook.h"
#include "UI/Button/NoteBook/UI_Button_NoteBook.h"
#include "UI/Controller/UI_Controller.h"
#include "Actor/Interact/Read/NoteBook/NoteBook.h"
#include "Asset/Manager/EHAssetManager.h"
#include <Blueprint/WidgetTree.h>
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

#pragma region Target

void UUI_PopUp_NoteBook::SetTarget(AActor* Target)
{
	if (!UI_NoteBooks.IsEmpty())
	{
		return;
	}

	Super::SetTarget(Target);

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

	constexpr uint8 WordLimit = 9;
	TArray<UWidget*> Childs;
	WidgetTree->GetChildWidgets(GetRootWidget(), OUT Childs);
	for (auto* Child : Childs)
	{
		auto* Btn = Cast<UUI_Button_NoteBook>(Child);
		if (IsValid(Btn) && Btn->GetName().Len() < WordLimit)
		{
			ZoomInButtons.Add(Btn);
		}
	}

	ZoomInButtons.Sort([](const UUI_Button_NoteBook& First, const UUI_Button_NoteBook& Second)
		{
			return First.GetName() < Second.GetName();
		});

	uint8 Index = 0;
	for (UUI_Button_NoteBook* Btn : ZoomInButtons)
	{
		Btn->ButtonIndex = Index++;
	}
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

#pragma region Page

void UUI_PopUp_NoteBook::TurnOverPage(bool bLeft)
{
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
		int32 DesIndex = PageStartIndex + Index;

		UUI_NoteBook* UI_NoteBook = UI_NoteBooks[Index].Get();
		UI_NoteBook->ChangeDescription(DesIndex);
		UI_NoteBook->SetVisibility(ESlateVisibility::Hidden);

		ZoomInButtons[Index]->ButtonIndex = DesIndex;

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