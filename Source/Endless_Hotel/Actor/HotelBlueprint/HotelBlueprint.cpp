// Copyright by 2026-1 WAP Game 2 team

#include "Actor/HotelBlueprint/HotelBlueprint.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/PopUp/HotelBlueprint/UI_PopUp_HotelBlueprint.h"
#include "Player/Controller/EHPlayerController.h"
#include "Component/Interact/InteractComponent.h"
#include <GameFramework/SpringArmComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>

#pragma region Interact

void AHotelBlueprint::Interact_Implementation(AEHCharacter* Interacter)
{
	MoveToBlueprint(Interacter);
}

#pragma endregion

#pragma region Move

void AHotelBlueprint::RestoreCamera()
{
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.UUID = 1;
	LatentInfo.Linkage = 0;
	LatentInfo.ExecutionFunction = FName("OnRestoreCompleted");

	UKismetSystemLibrary::MoveComponentTo(Comp_SpringArm.Get(), OriginalLoc, OriginalRot, true, true, 0.5f, true, EMoveComponentAction::Move, LatentInfo);
}

void AHotelBlueprint::MoveToBlueprint(AEHCharacter* Interacter)
{
	if (!IsValid(Player.Get()))
	{
		Player = Interacter;
	}

	auto* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PC->SetPlayerInputAble(false);

	if (!IsValid(Comp_SpringArm.Get()))
	{
		Comp_SpringArm = Player->FindComponentByClass<USpringArmComponent>();
	}

	OriginalLoc = Comp_SpringArm->GetComponentLocation();
	OriginalRot = Player->GetControlRotation();

	AdjustOffset = Comp_SpringArm->SocketOffset;

	Comp_SpringArm->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	Comp_SpringArm->bUsePawnControlRotation = false;
	Comp_SpringArm->SetWorldRotation(OriginalRot);

	FVector UpVector = GetActorUpVector();
	constexpr float UpLength = 25.f;

	FVector TargetLocation = GetActorLocation() + UpVector * UpLength;
	FRotator TargetRotation = FRotator(-90.f, GetActorRotation().Yaw, 0.f);

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.UUID = GetUniqueID();
	LatentInfo.Linkage = 0;
	LatentInfo.ExecutionFunction = FName("OnMoveCompleted");

	UKismetSystemLibrary::MoveComponentTo(Comp_SpringArm.Get(), TargetLocation, TargetRotation, true, true, 0.5f, true, EMoveComponentAction::Move, LatentInfo);
}

void AHotelBlueprint::OnMoveCompleted()
{
	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	auto* UI_HotelBlueprint = Cast<UUI_PopUp_HotelBlueprint>(UICon->OpenWidget(UI_HotelBlueprint_Class));

	UI_HotelBlueprint->SetHotelBlueprint(this);
}

void AHotelBlueprint::OnRestoreCompleted()
{
	Comp_SpringArm->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("HeadSocket"));
	Comp_SpringArm->bUsePawnControlRotation = true;
	Comp_SpringArm->SocketOffset = AdjustOffset;

	auto* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PC->SetPlayerInputAble(true);

	Component_Interact->RestoreInteract();
}

#pragma endregion