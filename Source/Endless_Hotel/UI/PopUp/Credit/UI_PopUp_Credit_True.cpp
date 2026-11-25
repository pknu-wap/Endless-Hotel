// Copyright by 2026-1 WAP Game 2 team

#include "UI/PopUp/Credit/UI_PopUp_Credit_True.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include <LevelSequencePlayer.h>

#pragma region Show

void UUI_PopUp_Credit_True::ShowWidget()
{
	Super::ShowWidget();

	FWidgetAnimationDynamicEvent AnimationFinished;
	AnimationFinished.BindDynamic(this, &ThisClass::OnFinishedAnimation);
	BindToAnimationFinished(WA_Credit, AnimationFinished);
	PlayAnimation(WA_Credit);

	FMovieSceneSequencePlaybackSettings Settings;
	ALevelSequenceActor* SequenceActor = nullptr;
	auto* LSPlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LS_Ending, Settings, OUT SequenceActor);
	LSPlayer->Play();
}

#pragma endregion

#pragma region Credit

void UUI_PopUp_Credit_True::OnFinishedAnimation()
{
	auto* GameInstance = GetGameInstance<UEHGameInstance>();
	GameInstance->QuitGame();
}

#pragma endregion