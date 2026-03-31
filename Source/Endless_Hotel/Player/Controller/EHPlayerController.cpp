// Copyright by 2025-2 WAP Game 2 team

#include "Player/Controller/EHPlayerController.h"
#include "Player/Character/EHPlayer.h"
#include "UI/Controller/UI_Controller.h"
#include "Component/Interact/InteractComponent.h"
#include "Type/UI/Type_UI_Key.h"
#include "Type/Save/Type_Save.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <InputMappingContext.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/PointLightComponent.h>
#include <Components/AudioComponent.h>

#pragma region Base

AEHPlayerController::AEHPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	bCanMove = true;
	bCanFaceCover = true;
	bIsCameraFixed = false;
	bIsPlayerDead = false;
}

void AEHPlayerController::BeginPlay()
{
	Super::BeginPlay();

	EHPlayer = Cast<AEHPlayer>(GetCharacter());
	UCameraComponent* PlayerCamera = EHPlayer->FindComponentByClass<UCameraComponent>();

	EHPlayer->FindComponentByClass<UPointLightComponent>()->SetVisibility(false);

	SpringArm = EHPlayer->FindComponentByClass<USpringArmComponent>();

	PlayerCameraManager->ViewPitchMin = -70.0f;
	PlayerCameraManager->ViewPitchMax = 70.0f;

	

	if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC_Default, 0);
	}

	IMC_Backup = IMC_Default;
}

void AEHPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CheckForInteractables();
	UpdateHeartbeatSound(DeltaSeconds);
}

#pragma endregion 

#pragma region Input

void AEHPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Move - 2D Vector로 통합
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);

		// Look - 2D Vector로 통합
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ThisClass::Look);

		// Run - Started/Completed 사용
		EnhancedInputComponent->BindAction(IA_Run, ETriggerEvent::Started, this, &ThisClass::OnRunStarted);
		EnhancedInputComponent->BindAction(IA_Run, ETriggerEvent::Completed, this, &ThisClass::OnRunCompleted);

		// Interact
		EnhancedInputComponent->BindAction(IA_Interact, ETriggerEvent::Started, this, &ThisClass::OnInteract);
		EnhancedInputComponent->BindAction(IA_ChangeInteract, ETriggerEvent::Started, this, &ThisClass::ChangeInteract);

		// Crouch - Started/Completed 사용
		EnhancedInputComponent->BindAction(IA_Crouch, ETriggerEvent::Started, this, &ThisClass::OnCrouchStarted);
		EnhancedInputComponent->BindAction(IA_Crouch, ETriggerEvent::Completed, this, &ThisClass::OnCrouchCompleted);

		// FaceCover
		EnhancedInputComponent->BindAction(IA_FaceCover, ETriggerEvent::Started, this, &ThisClass::OnFaceCoverStarted);
		EnhancedInputComponent->BindAction(IA_FaceCover, ETriggerEvent::Completed, this, &ThisClass::OnFaceCoverCompleted);

		// Light
		EnhancedInputComponent->BindAction(IA_Light, ETriggerEvent::Started, this, &ThisClass::TurnPlayerHandLight);

		//ESC
		EnhancedInputComponent->BindAction(IA_ESC, ETriggerEvent::Started, this, &ThisClass::EscapeStarted);
	}
}

#pragma endregion

#pragma region Component

UCameraComponent* AEHPlayerController::GetPlayerCamera() const
{
	if (EHPlayer.IsValid())
	{
		return EHPlayer->FindComponentByClass<UCameraComponent>();
	}
	return nullptr;
}

#pragma endregion

#pragma region Widget

void AEHPlayerController::EscapeStarted(const FInputActionValue& InputValue)
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(UI_Escape);
}

#pragma endregion 

#pragma region Move

void AEHPlayerController::Move(const FInputActionValue& Value)
{
	if (!bCanMove) return;

	if (!EHPlayer.IsValid()) return;

	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (MovementVector.SizeSquared() > 0.0f)
	{
		const FRotator YawRotation(0.0f, GetControlRotation().Yaw, 0.0f);
		const FRotationMatrix RotationMatrix(YawRotation);

		const FVector ForwardDirection = RotationMatrix.GetUnitAxis(EAxis::X);
		const FVector RightDirection = RotationMatrix.GetUnitAxis(EAxis::Y);

		EHPlayer->AddMovementInput(ForwardDirection, MovementVector.Y);
		EHPlayer->AddMovementInput(RightDirection, MovementVector.X);
	}
}

#pragma endregion

#pragma region Look

void AEHPlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();
	if (!bIsCameraFixed && LookVector.SizeSquared() > 0.0f)
	{
		AddYawInput(LookVector.X * LookSensitivity);
		AddPitchInput(LookVector.Y * LookSensitivity);
	}
}

#pragma endregion

#pragma region State_Run

void AEHPlayerController::OnRunStarted()
{
	if (!bCanRun)
	{
		return;
	}

	FVector Velocity = EHPlayer->GetVelocity();
	FRotator ActorRotation = EHPlayer->GetActorRotation();
	FVector LocalVelocity = ActorRotation.UnrotateVector(Velocity);

	if (LocalVelocity.X <= 0) {
		return;
	}

	bIsRunning = true;

	if (UCharacterMovementComponent* MovementComp = EHPlayer->GetCharacterMovement())
	{
		MovementComp->MaxWalkSpeed = RunSpeed;
	}
}

void AEHPlayerController::OnRunCompleted()
{
	if (!bCanRun)
	{
		return;
	}

	bIsRunning = false;

	if (UCharacterMovementComponent* MovementComp = EHPlayer->GetCharacterMovement())
	{
		MovementComp->MaxWalkSpeed = WalkSpeed;
	}
}

#pragma endregion

#pragma region State_Crouch

void AEHPlayerController::OnCrouchStarted()
{
	if (bIsCrouching) return;

	if (!bCanCrouch)
	{
		return;
	}

	bIsCrouching = true;

	EHPlayer->Crouch();
	EHPlayer->CrouchDelegate.Broadcast(bIsCrouching);
}

void AEHPlayerController::OnCrouchCompleted()
{
	if (!bIsCrouching) return;

	if (!bCanCrouch)
	{
		return;
	}

	bIsCrouching = false;

	EHPlayer->UnCrouch();
	EHPlayer->CrouchDelegate.Broadcast(bIsCrouching);
}

#pragma endregion

#pragma region State_FaceCover

void AEHPlayerController::OnFaceCoverStarted()
{
	if (!EHPlayer.IsValid()) return;
	if (!bCanFaceCover) return;

	FVector Velocity = EHPlayer->GetVelocity();
	float Speed = Velocity.Size();

	if (Speed > 0.0f) return; // 이동 중이면 전환 금지
	if (bIsFaceCoverTransitioning) return;

	bIsFaceCoverTransitioning = true;
	bIsFaceCovering = true;
	bIsCameraFixed = true;
	bCanMove = false;

	if (bIsFaceCovering) {
		SpringArm->AddRelativeLocation(FVector(-3.4f, -10.5f, 0.f));

		FRotator CurrentRotation = GetControlRotation();
		CurrentRotation.Pitch = -25.f;
		SetControlRotation(CurrentRotation);

		bIsFaceCoverTransitioning = false;
	}
}

void AEHPlayerController::OnFaceCoverCompleted()
{
	if (!EHPlayer.IsValid()) return;

	FVector Velocity = EHPlayer->GetVelocity();
	float Speed = Velocity.Size();

	if (!bIsFaceCovering) return;
	if (bIsFaceCoverTransitioning) return;

	bIsFaceCoverTransitioning = true;
	bIsFaceCovering = false;
	bIsCameraFixed = false;
	bCanMove = true;

	if (!bIsFaceCovering) {
		SpringArm->AddRelativeLocation(FVector(3.4f, 10.5f, 0.f));
		bIsFaceCoverTransitioning = false;
	}
}

#pragma endregion

#pragma region State_EVButton

void AEHPlayerController::OnEVButtonPressStarted()
{
	bIsButtonPressing = true;
	bIsCameraFixed = true;
	bCanMove = false;
}

void AEHPlayerController::OnEVButtonPressCompleted()
{
	bIsButtonPressing = false;
	bIsCameraFixed = false;
	bCanMove = true;
	bIsCameraFixed = false;
}

#pragma endregion

#pragma region State_HandLight

void AEHPlayerController::TurnPlayerHandLight()
{
	bHasFlash = USaveManager::LoadTutorialData().bHasFlash;

	if (!bCanMove || !bHasFlash)
	{
		return;
	}

	UPointLightComponent* Lighter = EHPlayer->FindComponentByClass<UPointLightComponent>();

	if (Lighter)
	{
		Lighter->ToggleVisibility();
	}
}

#pragma endregion

#pragma region State_Death

void AEHPlayerController::PlayDeathSequence()
{
	if (!EHPlayer.IsValid()) return;

	bIsPlayerDead = true;
	SetPlayerInputAble(false);
}

void AEHPlayerController::RevivePlayer()
{
	bIsPlayerDead = false;
	SetPlayerInputAble(true);
}
#pragma endregion

#pragma region State_FirstDoorOpen

void AEHPlayerController::OnFirstDoorOpenStarted()
{
	bIsPlayerDoorOpening = true;
	SpringArm->AddRelativeLocation(FVector(-3.4f, -10.5f, 0.f));

	FRotator CurrentRotation = GetControlRotation();
	CurrentRotation.Pitch = -25.f;
	SetControlRotation(CurrentRotation);

	SetPlayerInputAble(false);
}

void AEHPlayerController::OnFirstDoorOpenCompleted()
{
	bIsPlayerDoorOpening = false;
	SpringArm->AddRelativeLocation(FVector(3.4f, 10.5f, 0.f));

	SetPlayerInputAble(true);
}

void AEHPlayerController::OnPushDoorStarted()
{
	bIsPlayerPushingDoor = true;

	SetPlayerInputAble(false);
}

void AEHPlayerController::OnPushDoorCompleted()
{
	bIsPlayerPushingDoor = false;

	SetPlayerInputAble(true);
}

#pragma endregion

#pragma region Interact

void AEHPlayerController::CheckForInteractables()
{
	UCameraComponent* Camera = GetPlayerCamera();
	if (!Camera) return;

	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + Camera->GetForwardVector() * TraceDistance;

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(EHPlayer.Get());

	GetWorld()->LineTraceSingleByChannel(OUT HitResult, Start, End, ECC_Visibility, Params);

	auto* HitActor = HitResult.GetActor();
	UInteractComponent* HitComp = nullptr;
	if (HitActor)
	{
		HitComp = HitActor->FindComponentByClass<UInteractComponent>();
	}

	if (CachedInteractComp.Get())
	{
		CachedInteractComp->ShowInteracting(false);
		CachedInteractComp = nullptr;
	}

	if (HitComp)
	{
		HitComp->ShowInteracting(true);
		CachedInteractComp = HitComp;
	}

	EHPlayer->CanInteract.Broadcast(CachedInteractComp.IsValid() && CachedInteractComp->CanInteract());
}

void AEHPlayerController::OnInteract(const FInputActionValue& Value)
{
	if (!CachedInteractComp.Get() || !CachedInteractComp->CanInteract())
	{
		return;
	}

	if (bIsFaceCovering)
	{
		return;
	}

	CachedInteractComp->Interact(EHPlayer.Get());
}

void AEHPlayerController::ChangeInteract(const FInputActionValue& Value)
{
	if (!CachedInteractComp.Get() || !CachedInteractComp->CanInteract())
	{
		return;
	}

	float WheelValue = Value.Get<float>();
	bool bIsUp = WheelValue >= 0 ? true : false;

	CachedInteractComp->ChangeIndex(bIsUp);
}

#pragma endregion

#pragma region SetInput

void AEHPlayerController::SetPlayerInputAble(bool bAble)
{
	bCanMove = bAble;
	bCanFaceCover = bAble;
	bCanCrouch = bAble;
	bIsCameraFixed = !bAble;

	if (bAble)
	{
		ResetIgnoreLookInput();
	}
	else
	{
		SetIgnoreLookInput(true);
	}
}

#pragma endregion

#pragma region HeartBeatSound

void AEHPlayerController::SetHeartbeatSound(AActor* Monster)
{
	HeartbeatMonster = Monster;

	if (EHPlayer.IsValid() && !CachedHeartbeatComp)
	{
		CachedHeartbeatComp = EHPlayer->HeartbeatAudioComponent;
	}
}

void AEHPlayerController::StopHeartbeatSound()
{
	if (!CachedHeartbeatComp)
	{
		return;
	}

	CachedHeartbeatComp->Stop();
}

void AEHPlayerController::UpdateHeartbeatSound(float DeltaSeconds)
{
	if (!CachedHeartbeatComp || !HeartbeatMonster.IsValid() || EHPlayer->bIsDead)
	{
		if (CachedHeartbeatComp && CachedHeartbeatComp->IsPlaying())
		{
			CachedHeartbeatComp->Stop();
		}
		return;
	}

	float Distance = FVector::Dist(EHPlayer->GetActorLocation(), HeartbeatMonster->GetActorLocation());
	float TargetVolume = FMath::GetMappedRangeValueClamped(FVector2D(MaxDistance, MinDistance), FVector2D(0.0f, 1.2f), Distance);
	float TargetPitch = FMath::GetMappedRangeValueClamped(FVector2D(MaxDistance, MinDistance), FVector2D(1.0f, 2.0f), Distance);

	CachedHeartbeatComp->SetVolumeMultiplier(TargetVolume);
	CachedHeartbeatComp->SetPitchMultiplier(TargetPitch);

	if (TargetVolume > 0.01f && !CachedHeartbeatComp->IsPlaying())
	{
		CachedHeartbeatComp->Play();
	}
	else if (TargetVolume <= 0.01f && CachedHeartbeatComp->IsPlaying())
	{
		StopHeartbeatSound();
	}
}

#pragma endregion

#pragma region Key

void AEHPlayerController::SetKeyMapping(FKeySettingInfo NewInfo, FKey OldKey)
{
	IMC_Default->Modify();

	UInputAction* IA_Target = nullptr;
	TArray<UInputModifier*> SaveModifiers;

	auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	switch (NewInfo.Type)
	{
	case EKeySettingType::Up:
	case EKeySettingType::Down:
	case EKeySettingType::Left:
	case EKeySettingType::Right:
		IA_Target = IA_Move;
		break;

	case EKeySettingType::Run:
		IA_Target = IA_Run;
		break;

	case EKeySettingType::Sit:
		IA_Target = IA_Crouch;
		break;

	case EKeySettingType::Interact:
		IA_Target = IA_Interact;
		break;

	case EKeySettingType::Hide:
		IA_Target = IA_FaceCover;
		break;

	case EKeySettingType::Flash:
		IA_Target = IA_Light;
		break;

	case EKeySettingType::Reset:
		IMC_Default->UnmapAll();

		for (const auto& Mapping : IMC_Backup->GetMappings())
		{
			auto& NewMap = IMC_Default->MapKey(Mapping.Action, Mapping.Key);
			NewMap.Modifiers = Mapping.Modifiers;
		}

		Subsystem->RequestRebuildControlMappings();
		return;
	}

	for (const auto& Mapping : IMC_Default->GetMappings())
	{
		if (Mapping.Action == IA_Target && Mapping.Key == OldKey)
		{
			SaveModifiers = Mapping.Modifiers;
			break;
		}
	}

	IMC_Default->UnmapKey(IA_Target, OldKey);
	auto& Mapping = IMC_Default->MapKey(IA_Target, NewInfo.Value);
	Mapping.Modifiers = SaveModifiers;

	Subsystem->RequestRebuildControlMappings();
}

#pragma endregion
