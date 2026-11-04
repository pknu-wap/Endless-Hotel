// Copyright by 2026-1 WAP Game 2 team

#include "UI/PopUp/Credit/UI_PopUp_Credit_Bad.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/Base/NoteBook/UI_NoteBook.h"
#include "Player/Character/EHPlayer.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameSystem/SubSystem/EHGameSystem.h"
#include <Blueprint/WidgetTree.h>
#include <Kismet/GameplayStatics.h>

#pragma region Active

void UUI_PopUp_Credit_Bad::ActiveWidget()
{
	Super::ActiveWidget();

	UI_Pictures.Empty();

	TArray<UWidget*> Childs;
	WidgetTree->GetChildWidgets(GetRootWidget(), OUT Childs);
	for (auto* Child : Childs)
	{
		if (auto* UI_Picture = Cast<UUI_NoteBook>(Child))
		{
			UI_Pictures.Add(UI_Picture);
		}
	}

	UI_Pictures.Sort([](const UUI_NoteBook& First, const UUI_NoteBook& Second)
		{
			return First.GetName() < Second.GetName();
		});
}

#pragma endregion

#pragma region Show

void UUI_PopUp_Credit_Bad::ShowWidget()
{
	Super::ShowWidget();

	UGameplayStatics::PlaySound2D(GetWorld(), SW_CreditStart);

	FWidgetAnimationDynamicEvent AnimationFinished;
	AnimationFinished.BindDynamic(this, &ThisClass::OnFinishedAnimation);
	BindToAnimationFinished(WA_ShowLogo, AnimationFinished);
	PlayAnimation(WA_ShowLogo);

	for (int32 Index = 0; Index < UI_Pictures.Num(); ++Index)
	{
		UUI_NoteBook* UI_Picture = UI_Pictures[Index];
		UI_Picture->ChangeDescription(Index);
	}
}

#pragma endregion

#pragma region Credit

void UUI_PopUp_Credit_Bad::OnFinishedAnimation()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	auto* GameInstance = GetGameInstance<UEHGameInstance>();
	GameInstance->SwitchDataLayer(EMapDataLayer::Hotel);

	auto* GameSystem = GameInstance->GetSubsystem<UEHGameSystem>();
	GameSystem->ResetGameSystem();

	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->CloseWidget();
}

#pragma endregion