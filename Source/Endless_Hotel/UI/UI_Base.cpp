// Copyright by 2025-2 WAP Game 2 team

#include "UI/UI_Base.h"
#include <Blueprint/WidgetTree.h>

#pragma region Active

void UUI_Base::ActiveWidget()
{
	SetIsFocusable(true);

	SyncChildWidget(&ThisClass::ActiveWidget);
}

#pragma endregion

#pragma region Show & Hide

void UUI_Base::ShowWidget()
{
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	SetKeyboardFocus();

	SyncChildWidget(&ThisClass::ShowWidget);
}

void UUI_Base::HideWidget()
{
	SetVisibility(ESlateVisibility::Collapsed);

	SyncChildWidget(&ThisClass::HideWidget);
}

#pragma endregion

#pragma region Sync

void UUI_Base::SyncChildWidget(void(UUI_Base::* Func)())
{
	TArray<UWidget*> Widgets;
	WidgetTree->GetAllWidgets(OUT Widgets);
	for (auto* Widget : Widgets)
	{
		if (auto* Target = Cast<UUI_Base>(Widget))
		{
			(Target->*Func)();
		}
	}
}

#pragma endregion