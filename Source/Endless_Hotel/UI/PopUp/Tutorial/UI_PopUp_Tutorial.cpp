// Copyright by 2026-1 WAP Game 2 team

#include "UI/PopUp/Tutorial/UI_PopUp_Tutorial.h"
#include "UI/Controller/UI_Controller.h"
#include <Blueprint/WidgetTree.h>
#include <Components/Button.h>

#pragma region Base

void UUI_PopUp_Tutorial::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_ESC->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
}

#pragma endregion

#pragma region Show

void UUI_PopUp_Tutorial::ShowWidget()
{
	Super::ShowWidget();

	TArray<UWidget*> AllWidgets;
	WidgetTree->GetAllWidgets(OUT AllWidgets);

	for (UWidget* Widget : AllWidgets)
	{
		Widget->SetRenderOpacity(1.0f);
	}
}

#pragma endregion

#pragma region Input

void UUI_PopUp_Tutorial::Input_ESC()
{
	PlayAnimation(WidgetAnim_Disappear);

	constexpr float DisappearDuration = 1.0f;
	FTimerHandle CloseHandle;
	GetWorld()->GetTimerManager().SetTimer(CloseHandle, this, &ThisClass::CloseTutorial, DisappearDuration, false);
}

void UUI_PopUp_Tutorial::CloseTutorial()
{
	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->CloseWidget();
}

#pragma endregion