// Copyright by 2026-1 WAP Game 2 team

#include "UI/Base/Tutorial/UI_Tutorial.h"
#include <Components/TextBlock.h>

#pragma region Hide

void UUI_Tutorial::HideWidget()
{
	if (bNeedRemind)
	{
		bNeedRemind = false;
		return;
	}

	Super::HideWidget();
}

#pragma endregion

#pragma region Text

void UUI_Tutorial::SetTargetKey(const FText& Name)
{
	Text_Key->SetText(Name);
}

void UUI_Tutorial::SetTargetDescription(const FText& Name)
{
	Text_Description->SetText(Name);
}

#pragma endregion

#pragma region Animation

void UUI_Tutorial::ShowTutorialAnimation(bool bIsShow)
{
	UWidgetAnimation* Anim = bIsShow ? Anim_Show : Anim_Hide;

	PlayAnimation(Anim);
}

#pragma endregion

#pragma region Remind

void UUI_Tutorial::RemindManual()
{
	Super::ShowWidget();

	Text_Description->SetText(RemindText);
	Text_Description->SetRenderOpacity(1.f);

	bNeedRemind = true;
}

#pragma endregion