// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Default/Blur/UI_PopUp_Blur.h"
#include "Components/BackgroundBlur.h"

#pragma region Base

void UUI_PopUp_Blur::NativeConstruct()
{
	Super::NativeConstruct();

	StartSightBlur();
}

#pragma endregion

#pragma region Blur

void UUI_PopUp_Blur::StartSightBlur()
{
	const float TargetStrength = 20.f;
	float CurrentStrength = 0.f;

	TWeakObjectPtr<UUI_PopUp_Blur> Wrapper = this;
	GetWorld()->GetTimerManager().SetTimer(BlurHandle, [Wrapper, TargetStrength, CurrentStrength]() mutable
		{
			CurrentStrength += 0.1f;
			Wrapper->BackBlur->SetBlurStrength(CurrentStrength);

			if (CurrentStrength >= TargetStrength)
			{
				Wrapper->GetWorld()->GetTimerManager().ClearTimer(Wrapper->BlurHandle);
			}
		}, 0.01f, true);
}

#pragma endregion