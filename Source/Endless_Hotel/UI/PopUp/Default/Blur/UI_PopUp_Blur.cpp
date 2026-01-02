// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Default/Blur/UI_PopUp_Blur.h"
#include "Components/BackgroundBlur.h"

#pragma region Blur

void UUI_PopUp_Blur::AnomalyBlur()
{
	const float TargetStrength = 20;
	float CurrentStrength = 0;

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

void UUI_PopUp_Blur::EyeEffectBlur(bool bIsStart)
{
	float TargetStrength = 0;
	float CurrentStrength = 20;

	if (!bIsStart)
	{
		TargetStrength = 20;
		CurrentStrength = 0;
	}

	GetWorld()->GetTimerManager().SetTimer(BlurHandle, FTimerDelegate::CreateWeakLambda(this, [this, bIsStart, TargetStrength, CurrentStrength]() mutable
		{
			BackBlur->SetBlurStrength(CurrentStrength);

			if (bIsStart)
			{
				CurrentStrength -= 0.05f;

				if (CurrentStrength <= TargetStrength)
				{
					GetWorld()->GetTimerManager().ClearTimer(BlurHandle);
				}
			}
			else
			{
				CurrentStrength += 0.05f;

				if (CurrentStrength >= TargetStrength)
				{
					GetWorld()->GetTimerManager().ClearTimer(BlurHandle);
				}
			}
		}), 0.01f, true);
}

#pragma endregion