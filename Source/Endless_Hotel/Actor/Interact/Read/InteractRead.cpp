// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/Read/InteractRead.h"
#include "Player/Camera/EHPlayerCameraManager.h"
#include "Player/Controller/EHPlayerController.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/PopUp/Read/UI_PopUp_Read.h"
#include <Component/Interact/InteractComponent.h>
#include <Kismet/GameplayStatics.h>

#pragma region Interact

void AInteractRead::Interact_Implementation(AEHCharacter* Interacter)
{
	Super::Interact_Implementation(Interacter);

	FInteractInfo Info = Component_Interact->GetSelectedInteractInfo();

	switch (Info.InteractType)
	{
	case EInteractType::Read:
		PossessCamera(true);
		break;
	}
}

#pragma endregion

#pragma region Camera

void AInteractRead::PossessCamera(bool bIsReading)
{
	constexpr float Duration = 0.5f;

	auto* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PC->SetPlayerInputAble(!bIsReading);

	AActor* Target = bIsReading ? Cast<AActor>(this) : UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	auto* CameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	CameraManager->PossessCamera(Target, Duration);

	if (!bIsReading)
	{
		auto* Comp_Interact = FindComponentByClass<UInteractComponent>();
		Comp_Interact->RestoreInteract();
		return;
	}

	FTimerHandle WidgetHandle;
	GetWorld()->GetTimerManager().SetTimer(WidgetHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
			auto* UI_Read = Cast<UUI_PopUp_Read>(UICon->OpenWidget(UI_Read_Class));
			UI_Read->SetTarget(this);
		}), Duration, false);
}

#pragma endregion