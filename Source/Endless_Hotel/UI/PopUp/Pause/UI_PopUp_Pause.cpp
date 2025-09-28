// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Pause/UI_PopUp_Pause.h"
#include "Kismet/GameplayStatics.h"

#pragma region Base

void UUI_PopUp_Pause::NativeConstruct()
{
	Super::NativeConstruct();
	
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void UUI_PopUp_Pause::NativeDestruct()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	Super::NativeDestruct();
}

#pragma endregion