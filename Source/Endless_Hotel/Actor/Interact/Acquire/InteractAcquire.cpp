// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/Acquire/InteractAcquire.h"
#include "Player/Controller/EHPlayerController.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/PopUp/Acquire/UI_PopUp_Acquire.h"
#include <Camera/CameraComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>

#pragma region Interact

void AInteractAcquire::Interact(AEHCharacter* Interacter)
{
	Super::Interact(Interacter);

	FInteractInfo Info = Component_Interact->GetSelectedInteractInfo();

	switch (Info.InteractType)
	{
	case EInteractType::Pick:
		SaveAcquireData();
		MoveToPlayerCamera(Interacter);
		break;
	}
}

#pragma endregion

#pragma region Move

void AInteractAcquire::MoveToPlayerCamera(AEHCharacter* Interacter)
{
	auto* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PC->SetPlayerInputAble(false);

	auto* CameraComp = Interacter->FindComponentByClass<UCameraComponent>();

	FVector CameraLocation = CameraComp->GetComponentLocation();
	FVector ForwardVector = CameraComp->GetForwardVector();
	FVector UpVector = CameraComp->GetUpVector();

	FVector TargetLocation = CameraLocation + ForwardVector * ForwardLength + UpVector * UpLength;

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.UUID = 1;
	LatentInfo.Linkage = 0;
	LatentInfo.ExecutionFunction = FName("OnMoveCompleted");

	UKismetSystemLibrary::MoveComponentTo(RootComponent, TargetLocation, CameraComp->GetComponentRotation() + RotationOffset, true, true, 0.5f, false, EMoveComponentAction::Move, LatentInfo);
}

void AInteractAcquire::OnMoveCompleted()
{
	auto* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PC->SetPlayerInputAble(true);

	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	auto* UI_Acquire = Cast<UUI_PopUp_Acquire>(UICon->OpenWidget(EWidgetType::PopUp_Acquire));
	UI_Acquire->SetAcquireItem(this);
	UI_Acquire->SetInfoText(AcquireInfo);
}

#pragma endregion