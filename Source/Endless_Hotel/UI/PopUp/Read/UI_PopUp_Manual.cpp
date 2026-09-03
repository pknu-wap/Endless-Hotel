// Copyright by 2026-1 WAP Game 2 team

#include "UI/PopUp/Read/UI_PopUp_Manual.h"
#include "Actor/Interact/Read/Manual/Manual.h"
#include <Components/Button.h>

#pragma region Base

void UUI_PopUp_Manual::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Next->OnClicked.AddDynamic(this, &ThisClass::Click_ButtonNext);
	Button_Next->OnHovered.AddDynamic(this, &ThisClass::PlayArrowAnimation);
	Button_Next->OnUnhovered.AddDynamic(this, &ThisClass::StopArrowAnimation);
}

#pragma endregion

#pragma region Click

void UUI_PopUp_Manual::Click_ButtonNext()
{
	auto* Manual = Cast<AManual>(TargetObject);
	Manual->SwitchPaper();
}

#pragma endregion

#pragma region Animation

void UUI_PopUp_Manual::PlayArrowAnimation()
{
	PlayAnimation(WidgetAnim_Arrow, 0.f, 0);
}

void UUI_PopUp_Manual::StopArrowAnimation()
{
	StopAnimation(WidgetAnim_Arrow);
}

#pragma endregion