// Copyright by 2026-1 WAP Game 2 team

#include "UI/PopUp/Credit/UI_PopUp_Credit_Bad.h"
#include <Kismet/GameplayStatics.h>

#pragma region Show

void UUI_PopUp_Credit_Bad::ShowWidget()
{
	Super::ShowWidget();

	UGameplayStatics::PlaySound2D(GetWorld(), SW_CreditStart);

	PlayAnimation(WA_ShowLogo);
}

#pragma endregion