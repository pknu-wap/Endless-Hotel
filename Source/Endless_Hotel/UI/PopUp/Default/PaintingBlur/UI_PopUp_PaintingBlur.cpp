// Copyright by 2025-2 WAP Game 2 team


#include "UI/PopUp/Default/PaintingBlur/UI_PopUp_PaintingBlur.h"

#include "Components/BackgroundBlur.h"

#pragma region Base

void UUI_PopUp_PaintingBlur::NativeConstruct()
{
	Super::NativeConstruct();

	StartPaintingBlur();
}

#pragma endregion

#pragma region Blur

void UUI_PopUp_PaintingBlur::StartPaintingBlur()
{
	const float TargetStrength = 20.f;
	float CurrentStrength = 0.f;

	GetWorld()->GetTimerManager().SetTimer(BlurHandle, FTimerDelegate::CreateWeakLambda(this, [this, TargetStrength, CurrentStrength]() mutable
		{
			CurrentStrength += 0.1f;
			BackBlur->SetBlurStrength(CurrentStrength);

			if (CurrentStrength >= TargetStrength)
			{
				GetWorld()->GetTimerManager().ClearTimer(BlurHandle);
			}
		}), 0.01f, true);
}

#pragma endregion