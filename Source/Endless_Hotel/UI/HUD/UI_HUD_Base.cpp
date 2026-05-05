// Copyright by 2025-2 WAP Game 2 team

#include "UI/HUD/UI_HUD_Base.h"

#pragma region Base

void UUI_HUD_Base::NativeConstruct()
{
	Super::NativeConstruct();

	FTimerHandle CameraHandle;
	GetWorld()->GetTimerManager().SetTimer(CameraHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			//PossessCamera();
		}), 0.1f, false);
}

#pragma endregion