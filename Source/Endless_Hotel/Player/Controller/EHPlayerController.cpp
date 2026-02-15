// Copyright by 2025-2 WAP Game 2 team

#include "Player/Controller/EHPlayerController.h"
#include "Player/Character/EHPlayer.h"
#include "UI/Controller/UI_Controller.h"
#include "Component/Interact/InteractComponent.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/SpotLightComponent.h>

#pragma region Base

AEHPlayerController::AEHPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	bCanMove = true;
	bIsCameraFixed = false;
	bIsPlayerDead = false;
}

void AEHPlayerController::BeginPlay()
{
	Super::BeginPlay();

	EHPlayer = Cast<AEHPlayer>(GetCharacter());
	UCameraComponent* PlayerCamera = EHPlayer->FindComponentByClass<UCameraComponent>();

	FlashLight = EHPlayer->FindComponentByClass<USpotLightComponent>();
	if (FlashLight)
	{
		FlashLight->SetVisibility(false);
	}

	if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC_Default, 0);
	}
}

void AEHPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CheckForInteractables();
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
	if (EHPlayer)
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

#pragma endregion

#pragma region Look

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
	EHPlayer->CrouchDelegate.Broadcast(bIsCrouching);

	if (UCapsuleComponent* Capsule = EHPlayer->GetCapsuleComponent())
	{
		Capsule->SetCapsuleSize(45.f, 100.f);
	}
}

#pragma endregion

#pragma region State_Crouch

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
	bCanMove = true;
}

#pragma endregion

#pragma region State_HandLight

void AEHPlayerController::TurnPlayerHandLight()
{
	if (!bCanMove) {
		return;
	}

	if (!FlashLight)
	{
		FlashLight = EHPlayer->FindComponentByClass<USpotLightComponent>();
	}
	FlashLight->SetVisibility(!FlashLight->IsVisible());
}

#pragma endregion

#pragma region State_Death

void AEHPlayerController::PlayDeathSequence()
{
	if (!EHPlayer) return;

	bIsPlayerDead = true;
	bIsCameraFixed = true;
	bCanMove = false;

	if (!PlayerCameraComponent)
	{
		PlayerCameraComponent = EHPlayer->FindComponentByClass<UCameraComponent>();
	}

	PlayerCameraComponent->SetRelativeRotation(FRotator(-5.f, 0.f, 0.f));
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
	Params.AddIgnoredActor(EHPlayer);

	GetWorld()->LineTraceSingleByChannel(OUT HitResult, Start, End, ECC_Visibility, Params);

	auto* HitActor = HitResult.GetActor();
	UInteractComponent* HitComp = nullptr;
	if (HitActor)
	{
		HitComp = HitActor->FindComponentByClass<UInteractComponent>();
	}

	if (CachedInteractComp.Get())
	{
		CachedInteractComp->ShowDescriptionWidget(false);
		CachedInteractComp = nullptr;
	}

	if (HitComp)
	{
		HitComp->ShowDescriptionWidget(true);
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

	CachedInteractComp->Interact();
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