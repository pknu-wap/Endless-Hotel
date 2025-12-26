// Copyright by 2025-2 WAP Game 2 team

#include "Player/Controller/EHPlayerController.h"
#include "Player/Character/EHPlayer.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/PopUp/Default/Setting/UI_PopUp_Setting.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Interact/InteractableObject.h"

AEHPlayerController::AEHPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	// Interact
	bCanInteract = false;
	TraceDistance = 300.f;
	CurrentInteractActor = nullptr;

	UUI_PopUp_Setting::SettingSensitivity.AddDynamic(this, &ThisClass::SetLookSensitivity);
}

void AEHPlayerController::BeginPlay()
{
	Super::BeginPlay();

	EHPlayer = Cast<AEHPlayer>(GetCharacter());
	UCameraComponent* PlayerCamera = EHPlayer->FindComponentByClass<UCameraComponent>();

	if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC_Default, 0);
	}

	SetLookSensitivity(USaveManager::LoadSettingData().Value_Sensitivity);
}

void AEHPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CheckForInteractables();
}

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

		// Crouch - Started/Completed 사용
		EnhancedInputComponent->BindAction(IA_Crouch, ETriggerEvent::Started, this, &ThisClass::OnCrouchStarted);
		EnhancedInputComponent->BindAction(IA_Crouch, ETriggerEvent::Completed, this, &ThisClass::OnCrouchCompleted);

		// FaceCover
		EnhancedInputComponent->BindAction(IA_FaceCover, ETriggerEvent::Started, this, &ThisClass::OnFaceCoverStarted);
		EnhancedInputComponent->BindAction(IA_FaceCover, ETriggerEvent::Completed, this, &ThisClass::OnFaceCoverCompleted);

		//ESC
		EnhancedInputComponent->BindAction(IA_ESC, ETriggerEvent::Started, this, &ThisClass::EscapeStarted);
	}
}

void AEHPlayerController::Move(const FInputActionValue& Value)
{
	if (!bCanMove) return;

	if (!EHPlayer) return;

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

void AEHPlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();
	if (!bIsCameraFixed)
	{
		if (LookVector.SizeSquared() > 0.0f)
		{
			// Yaw (좌우)
			AddYawInput(LookVector.X * LookSensitivity);

			// Pitch (상하) - 카메라가 고정되지 않았을 때만

			if (UCameraComponent* CameraComponent = GetPlayerCamera())
			{
				FRotator CurrentRotation = CameraComponent->GetRelativeRotation();
				float NewPitch = CurrentRotation.Pitch + (LookVector.Y * LookSensitivity);
				NewPitch = FMath::Clamp(NewPitch, -70.0f, 70.0f);

				CameraComponent->SetRelativeRotation(FRotator(NewPitch, CurrentRotation.Yaw, CurrentRotation.Roll));
			}
		}
	}
}

void AEHPlayerController::OnRunStarted()
{
	if (!bCanRun)
	{
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

void AEHPlayerController::OnCrouchStarted()
{
	if (bIsCrouching) return;

	if (!bCanCrouch)
	{
		return;
	}

	bIsCrouching = true;

	EHPlayer->Crouch();

	if (UCapsuleComponent* Capsule = EHPlayer->GetCapsuleComponent())
	{
		Capsule->SetCapsuleSize(70.f, 60.f);
	}
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

	if (UCapsuleComponent* Capsule = EHPlayer->GetCapsuleComponent())
	{
		Capsule->SetCapsuleSize(45.f, 100.f);
	}
}

void AEHPlayerController::OnFaceCoverStarted()
{
	if (!EHPlayer) return;

	FVector Velocity = EHPlayer->GetVelocity();
	float Speed = Velocity.Size();

	if (Speed > 0.0f) return; // 이동 중이면 전환 금지
	if (bIsFaceCoverTransitioning) return;

	bIsFaceCoverTransitioning = true;
	bIsFaceCovering = true;
	bIsCameraFixed = true;
	bCanMove = false;

	// SpringArm & Camera 초기화
	if (!SpringArm)
	{
		SpringArm = EHPlayer->FindComponentByClass<USpringArmComponent>();
	}

	if (!PlayerCameraComponent)
	{
		PlayerCameraComponent = EHPlayer->FindComponentByClass<UCameraComponent>();
	}

	if (!SpringArm || !PlayerCameraComponent) return;


	if (bIsFaceCovering) {
		SpringArm->AddRelativeLocation(FVector(-3.4f, -10.5f, 0.f));
		PlayerCameraComponent->SetRelativeRotation(FRotator(-25.f, 0.f, 0.f));
		bIsFaceCoverTransitioning = false;
	}
}

void AEHPlayerController::OnFaceCoverCompleted()
{
	if (!EHPlayer) return;

	FVector Velocity = EHPlayer->GetVelocity();
	float Speed = Velocity.Size();

	if (!bIsFaceCovering) return;
	if (bIsFaceCoverTransitioning) return;

	bIsFaceCoverTransitioning = true;
	bIsFaceCovering = false;
	bIsCameraFixed = false;
	bCanMove = true;

	if (!SpringArm)
	{
		SpringArm = EHPlayer->FindComponentByClass<USpringArmComponent>();
	}

	if (!PlayerCameraComponent)
	{
		PlayerCameraComponent = EHPlayer->FindComponentByClass<UCameraComponent>();
	}

	if (!SpringArm || !PlayerCameraComponent) return;

	if (!bIsFaceCovering) {
		SpringArm->AddRelativeLocation(FVector(3.4f, 10.5f, 0.f));
		bIsFaceCoverTransitioning = false;
	}
}

void AEHPlayerController::CheckForInteractables()
{
	UCameraComponent* Camera = GetPlayerCamera();
	if (!Camera) return;

	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + Camera->GetForwardVector() * TraceDistance;

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetPawn());

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility,
		Params
	);

	// Debug line (시각 확인용)
	// DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.0f, 0, 1.0f);

	if (bHit && HitResult.GetActor())
	{
		AActor* HitActor = HitResult.GetActor();

		if (HitActor->GetClass()->ImplementsInterface(UInteractableObject::StaticClass()))
		{
			bCanInteract = true;
			CurrentInteractActor = HitActor;
			EHPlayer->CanInteract.Broadcast(true);
			return;
		}
	}

	// 트레이스 실패 or 유효하지 않음
	bCanInteract = false;
	CurrentInteractActor = nullptr;
	EHPlayer->CanInteract.Broadcast(false);
}

void AEHPlayerController::OnInteract(const FInputActionValue& Value)
{
	if (!bCanInteract || !CurrentInteractActor) return;

	if (CurrentInteractActor->GetClass()->ImplementsInterface(UInteractableObject::StaticClass()))
	{
		IInteractableObject::Execute_Interacted(CurrentInteractActor);
	}
}

void AEHPlayerController::EscapeStarted(const FInputActionValue& InputValue)
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(UI_Escape, EWidgetType::PopUp, EInputModeType::UIOnly);
}

UCameraComponent* AEHPlayerController::GetPlayerCamera() const
{
	if (EHPlayer)
	{
		return EHPlayer->FindComponentByClass<UCameraComponent>();
	}
	return nullptr;
}