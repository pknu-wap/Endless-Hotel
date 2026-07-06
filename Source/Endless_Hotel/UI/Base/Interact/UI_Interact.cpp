// Copyright by 2025-2 WAP Game 2 team

#include "UI/Base/Interact/UI_Interact.h"
#include <Components/TextBlock.h>
#include <Components/Image.h>

#pragma region Base

void UUI_Interact::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetVisibility(ESlateVisibility::Collapsed);
}

#pragma endregion

#pragma region Description

void UUI_Interact::SetDescription(FText Value)
{
	Text_Description->SetText(Value);
}

void UUI_Interact::ShowDescription(bool bIsShow, bool bNeedArrow)
{
	ESlateVisibility Target = bIsShow ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed;
	SetVisibility(Target);

	Target = bNeedArrow ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed;
	Image_Left->SetVisibility(Target);
	Image_Right->SetVisibility(Target);
}

#pragma endregion

#pragma region Animation

void UUI_Interact::PlayChangeAnimation(bool bUp)
{
	UWidgetAnimation* Anim = bUp ? Anim_Left : Anim_Right;
	PlayAnimation(Anim);
}

#pragma endregion