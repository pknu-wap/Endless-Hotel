// Copyright by 2026-1 WAP Game 2 team

#include "Component/Read/ReadComponent.h"
#include "Component/Interact/InteractComponent.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/PopUp/Read/UI_PopUp_Read.h"
#include "Player/Controller/EHPlayerController.h"
#include "Character/Character/EHCharacter.h"
#include <GameFramework/SpringArmComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>

#pragma region Reference

void UReadComponent::SetReferenceObject(AEHCharacter* Interacter, AActor* Target)
{
	if (!IsValid(TargetObject.Get()))
	{
		TargetObject = Target;
	}

	if (!IsValid(Player.Get()))
	{
		Player = Interacter;
	}

	if (!IsValid(Comp_SpringArm.Get()))
	{
		Comp_SpringArm = Player->FindComponentByClass<USpringArmComponent>();
	}

	if (!IsValid(Comp_Interact.Get()))
	{
		Comp_Interact = TargetObject->FindComponentByClass<UInteractComponent>();
	}
}

#pragma endregion

#pragma region Move

void UReadComponent::MoveCameraToTarget(AEHCharacter* Interacter, AActor* Target)
{
	SetReferenceObject(Interacter, Target);

	auto* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PC->SetPlayerInputAble(false);

	OriginalLoc = Comp_SpringArm->GetComponentLocation();
	OriginalRot = Player->GetControlRotation();

	Comp_SpringArm->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	Comp_SpringArm->bUsePawnControlRotation = false;
	Comp_SpringArm->SetWorldRotation(OriginalRot);

	FVector UpVector = TargetObject->GetActorUpVector();
	constexpr float UpLength = 25.f;

	FVector TargetLocation = TargetObject->GetActorLocation() + UpVector * UpLength;
	FRotator TargetRotation = FRotator(-90.f, TargetObject->GetActorRotation().Yaw, 0.f);

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.UUID = GetUniqueID();
	LatentInfo.Linkage = 0;
	LatentInfo.ExecutionFunction = FName("OnMoveCompleted");

	UKismetSystemLibrary::MoveComponentTo(Comp_SpringArm.Get(), TargetLocation, TargetRotation + RotOffset, true, true, 0.5f, true, EMoveComponentAction::Move, LatentInfo);
}

void UReadComponent::RestoreCamera()
{
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.UUID = 1;
	LatentInfo.Linkage = 0;
	LatentInfo.ExecutionFunction = FName("OnRestoreCompleted");

	UKismetSystemLibrary::MoveComponentTo(Comp_SpringArm.Get(), OriginalLoc, OriginalRot, true, true, 0.5f, true, EMoveComponentAction::Move, LatentInfo);
}

void UReadComponent::OnMoveCompleted()
{
	auto* UICon = GetWorld()->GetGameInstance()->GetSubsystem<UUI_Controller>();
	auto* UI_Read = Cast<UUI_PopUp_Read>(UICon->OpenWidget(UI_Read_Class));

	UI_Read->SetTarget(TargetObject.Get());
}

void UReadComponent::OnRestoreCompleted()
{
	Comp_SpringArm->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("HeadSocket"));
	Comp_SpringArm->bUsePawnControlRotation = true;

	auto* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PC->SetPlayerInputAble(true);

	Comp_Interact->RestoreInteract();
}

#pragma endregion