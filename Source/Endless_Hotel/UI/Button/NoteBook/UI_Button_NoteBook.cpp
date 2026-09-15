// Copyright by 2026-1 WAP Game 2 team

#include "UI/Button/NoteBook/UI_Button_NoteBook.h"
#include "UI/PopUp/Read/UI_PopUp_NoteBookZoomIn.h"
#include "UI/Controller/UI_Controller.h"

#pragma region Base

void UUI_Button_NoteBook::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button->OnClicked.AddDynamic(this, &ThisClass::Click_Button);
}

#pragma endregion

#pragma region Click

void UUI_Button_NoteBook::Click_Button()
{
	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	auto* UI_ZoomIn = Cast<UUI_PopUp_NoteBookZoomIn>(UICon->OpenWidget(EWidgetType::PopUp_NoteBookZoomIn));
	UI_ZoomIn->SetDescription(ButtonIndex);
}

#pragma endregion