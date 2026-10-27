// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/Bed/Bed_Ending.h"
#include "UI/Controller/UI_Controller.h"

#pragma region Base

ABed_Ending::ABed_Ending(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Comp_Direction = CreateDefaultSubobject<UBedDirectionComponent>(TEXT("Comp_Direction"));
}

#pragma endregion

#pragma region Interact

void ABed_Ending::Interact(AEHCharacter* Interacter)
{
	Super::Interact(Interacter);

	FInteractInfo Info = Component_Interact->GetSelectedInteractInfo();
	switch (Info.InteractType)
	{
	case EInteractType::Sleep:
		StartSleep();
		break;
	}
}

#pragma endregion

#pragma region Sleep

void ABed_Ending::StartSleep()
{
	Comp_Direction->SetPlayerInputAble(false);

	Comp_Direction->ShowDirection(SleepInfo);

	FTimerHandle EyeHandle;
	GetWorld()->GetTimerManager().SetTimer(EyeHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			Comp_Direction->ShowEyeEffect(false);
		}), 6.f, false);

	FTimerHandle WidgetHandle;
	GetWorld()->GetTimerManager().SetTimer(WidgetHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
			UICon->OpenWidget(EWidgetType::PopUp_Credit_Bad);
		}), 13.f, false);
}

#pragma endregion