// Copyright by 2026-1 WAP Game 2 team

#include "UI/PopUp/Credit/UI_PopUp_Credit_True.h"
#include <LevelSequencePlayer.h>

#pragma region Show

void UUI_PopUp_Credit_True::ShowWidget()
{
	Super::ShowWidget();

	PlayAnimation(WA_Credit);

	FMovieSceneSequencePlaybackSettings Settings;
	ALevelSequenceActor* SequenceActor = nullptr;
	auto* LSPlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LS_Ending, Settings, OUT SequenceActor);
	LSPlayer->Play();
}

#pragma endregion