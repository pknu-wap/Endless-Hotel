// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/Bed/Bed_Ending.h"
#include "UI/Controller/UI_Controller.h"
#include "Player/Character/EHPlayer.h"
#include <Kismet/GameplayStatics.h>

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
	Comp_Direction->SyncCameraRotation(true);
	Comp_Direction->SetPlayerInputAble(false);

	auto* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PC->SetControlRotation(SleepTrans.Rotator());

	auto* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->SetActorTransform(SleepTrans);
	Player->SetControlRotation(false);
	Player->SetCameraRotation(FRotator(0, 110, -90));
	Player->PlayAnimMontage(AM_Sleep);

	const float EyeDelay = 10.5f;
	FTimerHandle EyeHandle;
	GetWorld()->GetTimerManager().SetTimer(EyeHandle, FTimerDelegate::CreateUObject(Comp_Direction, &UBedDirectionComponent::ShowEyeEffect, false), EyeDelay, false);

	FTimerHandle WidgetHandle;
	GetWorld()->GetTimerManager().SetTimer(WidgetHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
			UICon->OpenWidget(EWidgetType::PopUp_Credit_Bad);
		}), 18.f, false);
}

#pragma endregion