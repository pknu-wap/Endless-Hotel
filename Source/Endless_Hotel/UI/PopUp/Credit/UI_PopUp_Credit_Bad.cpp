// Copyright by 2026-1 WAP Game 2 team

#include "UI/PopUp/Credit/UI_PopUp_Credit_Bad.h"
#include "UI/Controller/UI_Controller.h"
#include "Player/Character/EHPlayer.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameSystem/SubSystem/EHGameSystem.h"
#include <Kismet/GameplayStatics.h>

#pragma region Show

void UUI_PopUp_Credit_Bad::ShowWidget()
{
	Super::ShowWidget();

	UGameplayStatics::PlaySound2D(GetWorld(), SW_CreditStart);

	FWidgetAnimationDynamicEvent AnimationFinished;
	AnimationFinished.BindDynamic(this, &ThisClass::OnFinishedAnimation);
	BindToAnimationFinished(WA_ShowLogo, AnimationFinished);
	PlayAnimation(WA_ShowLogo);
}

#pragma endregion

#pragma region Restart

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